#pragma once
#include <atomic>
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
    void setVoiceGain(float g);
    void setBaseGain(float g);
    void setPan(float p);
    void setVoiceMute(bool m);
    void setBaseMute(bool m);
    void setMasterGain(float g);
    void setBypass(bool bypass);

    void process(const float* inL, const float* inR, float* outL, float* outR, int numSamples);

    bool isBypassed() const { return bypassed.load(); }
    float getOutRms() const { return outRms.load(); }
    float getVoiceRms() const { return voiceRms.load(); }
    float getBaseRms() const { return baseRms.load(); }

private:
    double sr = 44100.0;

    PitchShifter pitch;
    Delay delay;
    ReverbEffect reverb;
    PitchDetection detector;
    Mixer mixer;

    juce::AudioBuffer<float> tempVoice;
    juce::AudioBuffer<float> tempBase;
    juce::AudioBuffer<float> revTemp;

    std::atomic<float> voiceRms{ 0.0f };
    std::atomic<float> baseRms{ 0.0f };
    std::atomic<float> outRms{ 0.0f };
    std::atomic<bool> bypassed{ false };
    float masterGain = 1.0f;
};
