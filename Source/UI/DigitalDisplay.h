#pragma once
#include <juce_core/juce_core.h>
#include <juce_graphics/juce_graphics.h>
#include <juce_gui_basics/juce_gui_basics.h>

class DigitalDisplay : public juce::Component
{
public:
    DigitalDisplay(const juce::String& parameterName);
    ~DigitalDisplay() override = default;

    void setValue(const juce::String& text);
    void paint(juce::Graphics& g) override;
    void resized() override;

private:
    juce::String paramName;
    juce::String valueText{"0.00"};

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DigitalDisplay)
};
