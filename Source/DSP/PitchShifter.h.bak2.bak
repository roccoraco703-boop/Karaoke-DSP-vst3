#pragma once
#include <juce_core/juce_core.h>
#include <juce_events/juce_events.h>
#include <juce_graphics/juce_graphics.h>
#include <juce_gui_basics/juce_gui_basics.h>
#include <juce_audio_utils/juce_audio_utils.h>

class PitchShifter
{
public:
    PitchShifter();
    ~PitchShifter();

    void prepare(double sampleRate, int samplesPerBlock);

    void setSemitones(float st);

    void processBlock(float* input, float* output, int numSamples);

private:
    double sr = 44100.0;
    float semitones = 0.0f;

    float ratio = 1.0f;

    juce::AudioBuffer<float> buffer;
    int writePos = 0;

    void updateRatio();
};
