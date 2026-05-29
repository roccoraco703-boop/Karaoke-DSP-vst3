#include "Delay.h"

Delay::Delay()
{
}

Delay::~Delay()
{
}

void Delay::prepare(double sampleRate, int samplesPerBlock)
{
    sr = sampleRate;

    int maxDelaySamples = (int)(sr * 1.0); // max 1 secondo
    buffer.setSize(1, maxDelaySamples);
    buffer.clear();

    writePos = 0;
}

void Delay::setDelayTime(float time01)
{
    delayTime = juce::jlimit(0.0f, 1.0f, time01);
}

int Delay::getDelaySamples() const
{
    return (int)(delayTime * sr);
}

void Delay::processBlock(float* samples, int numSamples)
{
    auto* buf = buffer.getWritePointer(0);
    int bufSize = buffer.getNumSamples();

    int delaySamp = getDelaySamples();

    for (int i = 0; i < numSamples; i++)
    {
        buf[writePos] = samples[i];

        int readPos = writePos - delaySamp;
        if (readPos < 0)
            readPos += bufSize;

        float delayed = buf[readPos];

        samples[i] = samples[i] * 0.7f + delayed * 0.3f;

        writePos = (writePos + 1) % bufSize;
    }
}
