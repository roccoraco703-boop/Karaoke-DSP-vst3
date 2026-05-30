#include "ChannelStrip.h"

ChannelStrip::ChannelStrip(const juce::String& name)
    : channelName(name)
{
    // Nome
    nameLabel.setText(channelName, juce::dontSendNotification);
    nameLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(nameLabel);

    // Volume fader
    volumeSlider.setSliderStyle(juce::Slider::LinearVertical);
    volumeSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    volumeSlider.setRange(0.0, 1.0, 0.01);
    volumeSlider.setValue(0.75);
    addAndMakeVisible(volumeSlider);

    // Pan knob
    panSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    panSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    panSlider.setRange(-1.0, 1.0, 0.01);
    panSlider.setValue(0.0);
    addAndMakeVisible(panSlider);

    // Mute
    muteButton.setButtonText("M");
    addAndMakeVisible(muteButton);

    // Solo
    soloButton.setButtonText("S");
    addAndMakeVisible(soloButton);

    startTimerHz(30);
}

void ChannelStrip::setLevel(float newLevel)
{
    level = juce::jlimit(0.0f, 1.0f, newLevel);
}

void ChannelStrip::paint(juce::Graphics& g)
{
    auto bounds = getLocalBounds();

    // Sfondo pannello canale
    g.setColour(juce::Colour(0xFF151515));
    g.fillRect(bounds);

    // Bordo separatore
    g.setColour(juce::Colour(0xFF2A2A2A));
    g.drawVerticalLine(bounds.getRight() - 1, 0.0f, (float)bounds.getHeight());

    // LED meter area
    auto meterArea = bounds.removeFromRight(12).reduced(2);
    drawLedMeter(g, meterArea);
}

void ChannelStrip::drawLedMeter(juce::Graphics& g, juce::Rectangle<int> area)
{
    const int numSegments = 16;
    int segH = area.getHeight() / numSegments;
    int segW = area.getWidth() - 2;

    for (int i = 0; i < numSegments; ++i)
    {
        float segNorm = (float)i / (numSegments - 1);
        juce::Rectangle<int> seg(area.getX() + 1, area.getY() + (numSegments - 1 - i) * segH + 1, segW, segH - 2);

        bool on = level >= segNorm;
        if (on)
        {
            juce::Colour segCol;
            if (segNorm > 0.85f)
                segCol = juce::Colours::red;
            else if (segNorm > 0.6f)
                segCol = juce::Colours::orange;
            else
                segCol = juce::Colours::limegreen;

            g.setColour(segCol);
            g.fillRect(seg);
            // Glow
            g.setColour(segCol.withAlpha(0.3f));
            g.fillRect(seg.expanded(1));
        }
        else
        {
            g.setColour(juce::Colour(0xFF1A1A1A));
            g.fillRect(seg);
        }

        g.setColour(juce::Colour(0xFF0A0A0A));
        g.drawRect(seg, 1);
    }
}

void ChannelStrip::timerCallback()
{
    repaint();
}

void ChannelStrip::resized()
{
    auto area = getLocalBounds().reduced(4);
    area.removeFromRight(14); // spazio per LED meter

    auto top = area.removeFromTop(20);
    nameLabel.setBounds(top);

    auto bottom = area.removeFromBottom(70);
    auto btnRow = bottom.removeFromTop(24);
    muteButton.setBounds(btnRow.removeFromLeft(btnRow.getWidth() / 2));
    soloButton.setBounds(btnRow);
    panSlider.setBounds(bottom);

    volumeSlider.setBounds(area);
}
