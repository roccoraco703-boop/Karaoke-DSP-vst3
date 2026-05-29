#pragma once
#include <juce_core/juce_core.h>
#include <juce_events/juce_events.h>
#include <juce_graphics/juce_graphics.h>
#include <juce_gui_basics/juce_gui_basics.h>
#include <juce_audio_utils/juce_audio_utils.h>

class Knob : public juce::Component
{
public:
    Knob(const juce::String& labelText);
    ~Knob() override = default;

    void paint(juce::Graphics&) override;
    void resized() override;

    void setRange(double min, double max, double step);
    void setValue(double newValue);
    double getValue() const;

    juce::Slider& getSlider() { return slider; }

private:
    juce::Slider slider;
    juce::Label label;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Knob)
};
