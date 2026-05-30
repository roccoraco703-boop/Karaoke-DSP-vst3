#include "Mixer.h"

Mixer::Mixer()
{
}

Mixer::~Mixer()
{
}

void Mixer::prepare(double sampleRate)
{
    sr = sampleRate;
}

void Mixer::setVoiceGain(float g)
{
    voiceGain = juce::jlimit(0.0f, 2.0f, g);
}

void Mixer::setBaseGain(float g)
{
    baseGain = juce::jlimit(0.0f, 2.0f, g);
}

void Mixer::setPan(float p)
{
    pan = juce::jlimit(-1.0f, 1.0f, p);
}

void Mixer::setVoiceMute(bool m)
{
    voiceMute = m;
}

void Mixer::setBaseMute(bool m)
{
    baseMute = m;
}

void Mixer::process(float* voice, float* base, float* outL, float* outR, int numSamples)
{
    float leftPan  = (pan <= 0.0f) ? 1.0f : (1.0f - pan);
    float rightPan = (pan >= 0.0f) ? 1.0f : (1.0f + pan);

    for (int i = 0; i < numSamples; i++)
    {
        float v = voiceMute ? 0.0f : voice[i] * voiceGain;
        float b = baseMute  ? 0.0f : base[i]  * baseGain;

        float mix = v + b;
        mix = juce::jlimit(-1.0f, 1.0f, mix);

        outL[i] = mix * leftPan;
        outR[i] = mix * rightPan;
    }
}
