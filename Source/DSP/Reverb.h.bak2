#pragma once
#include <juce_core/juce_core.h>
#include <juce_events/juce_events.h>
#include <juce_graphics/juce_graphics.h>
#include <juce_gui_basics/juce_gui_basics.h>
#include <juce_audio_utils/juce_audio_utils.h>

class ReverbEffect
{
public:
    ReverbEffect();
    ~ReverbEffect();

    void prepare(double sampleRate, int samplesPerBlock);

    void setWetLevel(float amount01);

    void processBlock(float* input, float* outL, float* outR, int numSamples);

private:
    double sr = 44100.0;

    juce::Reverb reverb;
    juce::Reverb::Parameters params;
};
