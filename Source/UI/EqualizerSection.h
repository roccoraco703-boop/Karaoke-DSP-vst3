#pragma once
#include <juce_gui_basics/juce_gui_basics.h>
#include "Knob.h"

class EqualizerSection : public juce::Component
{
public:
    EqualizerSection();
    ~EqualizerSection() override = default;

    void paint(juce::Graphics& g) override;
    void resized() override;

    juce::Slider& getLowKnob()  { return lowKnob.getSlider(); }
    juce::Slider& getMid1Knob() { return mid1Knob.getSlider(); }
    juce::Slider& getMid2Knob() { return mid2Knob.getSlider(); }
    juce::Slider& getHighKnob() { return highKnob.getSlider(); }

private:
    juce::Label titleLabel;
    Knob lowKnob{"PITCH"};
    Knob mid1Knob{"DELAY"};
    Knob mid2Knob{"REVERB"};
    Knob highKnob{"GAIN"};

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(EqualizerSection)
};
