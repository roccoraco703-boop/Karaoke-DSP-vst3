#include "PitchDetection.h"

PitchDetection::PitchDetection()
{
}

PitchDetection::~PitchDetection()
{
}

void PitchDetection::prepare(double sampleRate)
{
    sr = sampleRate;
}

void PitchDetection::processBlock(float* samples, int numSamples)
{
    lastPitch = detectPitch(samples, numSamples);
}

float PitchDetection::detectPitch(float* samples, int numSamples)
{
    // Metodo semplicissimo: trova il valore massimo e usa la sua posizione
    // come pseudo-frequenza (NON è un vero pitch detection).
    // Solo per esempio.
    int maxIndex = 0;
    float maxValue = 0.0f;

    for (int i = 0; i < numSamples; i++)
    {
        float v = std::abs(samples[i]);
        if (v > maxValue)
        {
            maxValue = v;
            maxIndex = i;
        }
    }

    if (maxIndex == 0)
        return 0.0f;

    float freq = sr / (float)maxIndex;
    return freq;
}
