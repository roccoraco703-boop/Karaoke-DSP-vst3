#pragma once
#include <juce_core/juce_core.h>
#include <juce_events/juce_events.h>
#include <juce_graphics/juce_graphics.h>
#include <juce_gui_basics/juce_gui_basics.h>
#include <juce_audio_utils/juce_audio_utils.h>

class VuMeter : public juce::Component
{
public:
    VuMeter() {}
    ~VuMeter() override {}

    void setLevel(float newLevel)
    {
        level = juce::jlimit(0.0f, 1.0f, newLevel);
    }

    void paint(juce::Graphics& g) override
    {
        g.fillAll(juce::Colours::black);

        auto area = getLocalBounds().reduced(4);

        g.setColour(juce::Colours::darkgrey);
        g.fillRect(area);

        int h = area.getHeight();
        int filled = (int)(h * level);

        g.setColour(juce::Colours::limegreen);
        g.fillRect(area.removeFromBottom(filled));
    }

private:
    float level = 0.0f;
};
