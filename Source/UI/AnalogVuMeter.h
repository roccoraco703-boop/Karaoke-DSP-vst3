#pragma once
#include <juce_core/juce_core.h>
#include <juce_events/juce_events.h>
#include <juce_graphics/juce_graphics.h>
#include <juce_gui_basics/juce_gui_basics.h>

class AnalogVuMeter : public juce::Component,
                      private juce::Timer
{
public:
    AnalogVuMeter();
    ~AnalogVuMeter() override = default;

    void setLevel(float newLevel); // 0..1
    float getLevel() const { return level; }

    void paint(juce::Graphics& g) override;
    void resized() override;
    void timerCallback() override;

private:
    float level = 0.0f;
    float smoothLevel = 0.0f;

    static constexpr float startAngle = juce::MathConstants<float>::pi * 1.25f;  // -135 deg
    static constexpr float endAngle   = juce::MathConstants<float>::pi * -0.25f; // +45  deg (clockwise)

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AnalogVuMeter)
};
