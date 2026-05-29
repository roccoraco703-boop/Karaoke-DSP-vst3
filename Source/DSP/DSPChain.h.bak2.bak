#pragma once
#include <juce_core/juce_core.h>
#include <juce_events/juce_events.h>
#include <juce_graphics/juce_graphics.h>
#include <juce_gui_basics/juce_gui_basics.h>
#include <juce_audio_utils/juce_audio_utils.h>

#include "PitchShifter.h"
#include "Delay.h"
#include "Reverb.h"
#include "PitchDetection.h"
#include "Mixer.h"

class DSPChain
{
public:
    DSPChain();
    ~DSPChain();

    void prepare(double sampleRate, int samplesPerBlock);

    void setPitch(float semitones);
    void setDelay(float time);
    void setReverb(float amount);

    void process(float* outL, float* outR, int numSamples);

private:
    double sr = 44100.0;

    PitchShifter pitch;
    Delay delay;
    ReverbEffect reverb;
    PitchDetection detector;
    Mixer mixer;

    juce::AudioBuffer<float> tempVoice;
    juce::AudioBuffer<float> tempBase;
};
