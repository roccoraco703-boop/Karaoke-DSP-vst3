#pragma once
#include <juce_gui_basics/juce_gui_basics.h>

class ChannelStrip : public juce::Component,
                       private juce::Timer
{
public:
    ChannelStrip(const juce::String& name);
    ~ChannelStrip() override = default;

    void setLevel(float newLevel); // 0..1
    void paint(juce::Graphics& g) override;
    void resized() override;

    void timerCallback() override;

    juce::Slider& getVolumeSlider() { return volumeSlider; }
    juce::Slider& getPanSlider()    { return panSlider; }
    juce::TextButton& getMuteButton() { return muteButton; }
    juce::TextButton& getSoloButton() { return soloButton; }

private:
    juce::String channelName;
    float level = 0.0f;

    juce::Label nameLabel;
    juce::Slider volumeSlider;
    juce::Slider panSlider;
    juce::TextButton muteButton;
    juce::TextButton soloButton;

    void drawLedMeter(juce::Graphics& g, juce::Rectangle<int> area);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ChannelStrip)
};
