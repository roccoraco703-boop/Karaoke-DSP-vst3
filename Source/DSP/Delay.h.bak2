#pragma once
#include <juce_core/juce_core.h>
#include <juce_events/juce_events.h>
#include <juce_graphics/juce_graphics.h>
#include <juce_gui_basics/juce_gui_basics.h>
#include <juce_audio_utils/juce_audio_utils.h>

class Delay
{
public:
    Delay();
    ~Delay();

    void prepare(double sampleRate, int samplesPerBlock);

    void setDelayTime(float time01);

    void processBlock(float* samples, int numSamples);

private:
    double sr = 44100.0;

    juce::AudioBuffer<float> buffer;
    int writePos = 0;

    float delayTime = 0.3f; // 0..1 → 0..1 second

    int getDelaySamples() const;
};
