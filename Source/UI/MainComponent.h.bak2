#pragma once
#include <juce_gui_basics/juce_gui_basics.h>

#include "../DSP/DSPChain.h"
#include "Knob.h"
#include "VuMeter.h"

class MainComponent : public juce::Component,
                      public juce::Timer
{
public:
    MainComponent();
    ~MainComponent() override;

    void paint(juce::Graphics&) override;
    void resized() override;

    void timerCallback() override;

private:
    DSPChain dsp;

    Knob pitchKnob{"Pitch"};
    Knob delayKnob{"Delay"};
    Knob reverbKnob{"Reverb"};

    VuMeter vu;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainComponent)
};
