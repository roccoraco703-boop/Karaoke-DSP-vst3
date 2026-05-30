#pragma once
#include <juce_core/juce_core.h>
#include <juce_events/juce_events.h>
#include <juce_graphics/juce_graphics.h>
#include <juce_gui_basics/juce_gui_basics.h>
#include <juce_audio_utils/juce_audio_utils.h>

class Mixer
{
public:
    Mixer();
    ~Mixer();

    void prepare(double sampleRate);

    void setVoiceGain(float g);
    void setBaseGain(float g);
    void setPan(float p);
    void setVoiceMute(bool m);
    void setBaseMute(bool m);

    void process(float* voice, float* base, float* outL, float* outR, int numSamples);

private:
    double sr = 44100.0;

    float voiceGain = 0.8f;
    float baseGain  = 0.5f;
    float pan = 0.0f;
    bool voiceMute = false;
    bool baseMute = false;
};
