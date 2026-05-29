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

void DSPChain::process(float* outL, float* outR, int numSamples)
{
    auto* voice = tempVoice.getWritePointer(0);
    auto* base  = tempBase.getWritePointer(0);

    // 1) Pitch shifting
    pitch.processBlock(outL, voice, numSamples);

    // 2) Delay
    delay.processBlock(voice, numSamples);

    // 3) Reverb
    float* revL = new float[numSamples];
    float* revR = new float[numSamples];
    reverb.processBlock(voice, revL, revR, numSamples);

    // 4) Pitch detection (solo analisi)
    detector.processBlock(voice, numSamples);

    // 5) Base = reverb L (semplice esempio)
    for (int i = 0; i < numSamples; i++)
        base[i] = revL[i];

    // 6) Mix finale
    mixer.process(voice, base, outL, outR, numSamples);

    delete[] revL;
    delete[] revR;
}
