#pragma once
#include <juce_core/juce_core.h>
#include <juce_events/juce_events.h>
#include <juce_graphics/juce_graphics.h>
#include <juce_gui_basics/juce_gui_basics.h>
#include <juce_audio_utils/juce_audio_utils.h>

class PitchDetection
{
public:
    PitchDetection();
    ~PitchDetection();

    void prepare(double sampleRate);

    void processBlock(float* samples, int numSamples);

    float getLastPitch() const { return lastPitch; }

private:
    double sr = 44100.0;

    float lastPitch = 0.0f;

    float detectPitch(float* samples, int numSamples);
};
