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

void Mixer::process(float* voice, float* base, float* outL, float* outR, int numSamples)
{
    for (int i = 0; i < numSamples; i++)
    {
        float v = voice[i] * voiceGain;
        float b = base[i]  * baseGain;

        float mix = v + b;

        outL[i] = mix;
        outR[i] = mix;
    }
}
