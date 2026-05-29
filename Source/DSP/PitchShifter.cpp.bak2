#include "PitchShifter.h"

PitchShifter::PitchShifter()
{
}

PitchShifter::~PitchShifter()
{
}

void PitchShifter::prepare(double sampleRate, int samplesPerBlock)
{
    sr = sampleRate;
    buffer.setSize(1, samplesPerBlock * 4);
    buffer.clear();
    writePos = 0;

    updateRatio();
}

void PitchShifter::setSemitones(float st)
{
    semitones = st;
    updateRatio();
}

void PitchShifter::updateRatio()
{
    ratio = std::pow(2.0f, semitones / 12.0f);
}

void PitchShifter::processBlock(float* input, float* output, int numSamples)
{
    auto* buf = buffer.getWritePointer(0);
    int bufSize = buffer.getNumSamples();

    for (int i = 0; i < numSamples; i++)
    {
        buf[writePos] = input[i];
        writePos = (writePos + 1) % bufSize;
    }

    float readPos = (float)writePos - (float)numSamples * ratio;
    if (readPos < 0)
        readPos += bufSize;

    for (int i = 0; i < numSamples; i++)
    {
        int i1 = (int)readPos;
        int i2 = (i1 + 1) % bufSize;
        float frac = readPos - (float)i1;

        float s = buf[i1] * (1.0f - frac) + buf[i2] * frac;

        output[i] = s;

        readPos += ratio;
        if (readPos >= bufSize)
            readPos -= bufSize;
    }
}
