#include "Reverb.h"

ReverbEffect::ReverbEffect()
{
    params.roomSize   = 0.5f;
    params.damping    = 0.5f;
    params.width      = 1.0f;
    params.freezeMode = 0.0f;
    params.wetLevel   = 0.3f;
    params.dryLevel   = 0.7f;
}

ReverbEffect::~ReverbEffect()
{
}

void ReverbEffect::prepare(double sampleRate, int samplesPerBlock)
{
    sr = sampleRate;
    temp.setSize(2, samplesPerBlock);
    reverb.setParameters(params);
}

void ReverbEffect::setWetLevel(float amount01)
{
    params.wetLevel = juce::jlimit(0.0f, 1.0f, amount01);
    params.dryLevel = 1.0f - params.wetLevel;
    reverb.setParameters(params);
}

void ReverbEffect::processBlock(float* input, float* outL, float* outR, int numSamples)
{
    auto* L = temp.getWritePointer(0);
    auto* R = temp.getWritePointer(1);

    for (int i = 0; i < numSamples; i++)
    {
        L[i] = input[i];
        R[i] = input[i];
    }

    reverb.processStereo(L, R, numSamples);

    for (int i = 0; i < numSamples; i++)
    {
        outL[i] = L[i];
        outR[i] = R[i];
    }
}
