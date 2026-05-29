#pragma once
#include <juce_gui_basics/juce_gui_basics.h>

class MixerChannelComponent : public juce::Component
{
public:
    MixerChannelComponent(const juce::String& name)
        : channelName(name)
    {
        addAndMakeVisible(volumeSlider);
        volumeSlider.setSliderStyle(juce::Slider::LinearVertical);
        volumeSlider.setRange(0.0, 1.0, 0.01);
        volumeSlider.setValue(0.75);

        addAndMakeVisible(panSlider);
        panSlider.setSliderStyle(juce::Slider::Rotary);
        panSlider.setRange(-1.0, 1.0, 0.01);
        panSlider.setValue(0.0);

        addAndMakeVisible(muteButton);
        muteButton.setButtonText("M");

        addAndMakeVisible(soloButton);
        soloButton.setButtonText("S");
    }

    void resized() override
    {
        auto area = getLocalBounds().reduced(4);

        auto top = area.removeFromTop(20);
        channelLabel.setText(channelName, juce::dontSendNotification);
        channelLabel.setJustificationType(juce::Justification::centred);
        channelLabel.setBounds(top);

        volumeSlider.setBounds(area.removeFromLeft(40));
        panSlider.setBounds(area.removeFromTop(60));

        auto buttons = area.removeFromTop(30);
        muteButton.setBounds(buttons.removeFromLeft(30));
        soloButton.setBounds(buttons.removeFromLeft(30));
    }

private:
    juce::String channelName;

    juce::Label channelLabel;
    juce::Slider volumeSlider;
    juce::Slider panSlider;
    juce::TextButton muteButton;
    juce::TextButton soloButton;
};
