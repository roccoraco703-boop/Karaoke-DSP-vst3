#include "DSPChain.h"

DSPChain::DSPChain()
{
}

DSPChain::~DSPChain()
{
}

void DSPChain::prepare(double sampleRate, int samplesPerBlock)
{
    sr = sampleRate;

    pitch.prepare(sampleRate, samplesPerBlock);
    delay.prepare(sampleRate, samplesPerBlock);
    reverb.prepare(sampleRate, samplesPerBlock);
    detector.prepare(sampleRate);
    mixer.prepare(sampleRate);

    tempVoice.setSize(1, samplesPerBlock);
    tempBase.setSize(1, samplesPerBlock);
    revTemp.setSize(2, samplesPerBlock);
}

void DSPChain::setPitch(float semitones)
{
    pitch.setSemitones(semitones);
}

void DSPChain::setDelay(float time)
{
    delay.setDelayTime(time);
}

void DSPChain::setReverb(float amount)
{
    reverb.setWetLevel(amount);
}

void DSPChain::setVoiceGain(float g)
{
    mixer.setVoiceGain(g);
}

void DSPChain::setBaseGain(float g)
{
    mixer.setBaseGain(g);
}

void DSPChain::setPan(float p)
{
    mixer.setPan(p);
}

void DSPChain::setVoiceMute(bool m)
{
    mixer.setVoiceMute(m);
}

void DSPChain::setBaseMute(bool m)
{
    mixer.setBaseMute(m);
}

void DSPChain::setMasterGain(float g)
{
    masterGain = juce::jlimit(0.0f, 2.0f, g);
}

void DSPChain::setBypass(bool bypass)
{
    bypassed.store(bypass);
}

void DSPChain::process(const float* inL, const float* inR, float* outL, float* outR, int numSamples)
{
    if (bypassed.load())
    {
        for (int i = 0; i < numSamples; i++)
        {
            outL[i] = inL[i];
            outR[i] = inR[i];
        }
        // Calcola livelli anche in bypass
        float oSum = 0.0f;
        for (int i = 0; i < numSamples; i++)
            oSum += outL[i] * outL[i] + outR[i] * outR[i];
        outRms.store(std::sqrt(oSum / (numSamples * 2)));
        voiceRms.store(outRms.load());
        baseRms.store(0.0f);
        return;
    }


    auto* voice = tempVoice.getWritePointer(0);
    auto* base  = tempBase.getWritePointer(0);

    // Mix input stereo to mono voice
    for (int i = 0; i < numSamples; i++)
        voice[i] = (inL[i] + inR[i]) * 0.5f;

    // 1) Pitch shifting
    pitch.processBlock(voice, voice, numSamples);

    // 2) Delay
    delay.processBlock(voice, numSamples);

    // 3) Reverb
    auto* revL = revTemp.getWritePointer(0);
    auto* revR = revTemp.getWritePointer(1);
    reverb.processBlock(voice, revL, revR, numSamples);

    // 4) Pitch detection (solo analisi)
    detector.processBlock(voice, numSamples);

    // 5) Base = reverb L
    for (int i = 0; i < numSamples; i++)
        base[i] = revL[i];

    // 6) Mix finale
    mixer.process(voice, base, outL, outR, numSamples);

    // 7) Master gain
    for (int i = 0; i < numSamples; i++)
    {
        outL[i] *= masterGain;
        outR[i] *= masterGain;
    }

    // Calcola RMS per UI meters
    float vSum = 0.0f, bSum = 0.0f, oSum = 0.0f;
    for (int i = 0; i < numSamples; i++)
    {
        vSum += voice[i] * voice[i];
        bSum += base[i]  * base[i];
        oSum += outL[i]  * outL[i] + outR[i] * outR[i];
    }
    voiceRms.store(std::sqrt(vSum / numSamples));
    baseRms.store(std::sqrt(bSum / numSamples));
    outRms.store(std::sqrt(oSum / (numSamples * 2)));
}
