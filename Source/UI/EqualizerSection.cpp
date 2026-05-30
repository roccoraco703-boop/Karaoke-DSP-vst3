#include "EqualizerSection.h"

EqualizerSection::EqualizerSection()
{
    titleLabel.setText("EQ", juce::dontSendNotification);
    titleLabel.setJustificationType(juce::Justification::centred);
    titleLabel.setFont(juce::Font(juce::FontOptions(juce::Font::getDefaultSansSerifFontName(), 14.0f, juce::Font::bold)));
    titleLabel.setColour(juce::Label::textColourId, juce::Colour(0xFF00E5FF));
    addAndMakeVisible(titleLabel);

    lowKnob.getSlider().setRange(-12.0, 12.0, 0.1);
    lowKnob.getSlider().setValue(0.0);
    addAndMakeVisible(lowKnob);

    mid1Knob.getSlider().setRange(0.0, 1.0, 0.01);
    mid1Knob.getSlider().setValue(0.3);
    addAndMakeVisible(mid1Knob);

    mid2Knob.getSlider().setRange(0.0, 1.0, 0.01);
    mid2Knob.getSlider().setValue(0.3);
    addAndMakeVisible(mid2Knob);

    highKnob.getSlider().setRange(0.0, 2.0, 0.01);
    highKnob.getSlider().setValue(1.0);
    addAndMakeVisible(highKnob);
}

void EqualizerSection::paint(juce::Graphics& g)
{
    auto bounds = getLocalBounds().toFloat();

    // Sfondo pannello
    g.setColour(juce::Colour(0xFF121212));
    g.fillRoundedRectangle(bounds, 6.0f);

    // Bordo
    g.setColour(juce::Colour(0xFF2A2A2A));
    g.drawRoundedRectangle(bounds.reduced(1.0f), 6.0f, 1.5f);
}

void EqualizerSection::resized()
{
    auto area = getLocalBounds().reduced(8);

    auto top = area.removeFromTop(20);
    titleLabel.setBounds(top);

    int knobW = area.getWidth() / 4;
    lowKnob.setBounds(area.removeFromLeft(knobW));
    mid1Knob.setBounds(area.removeFromLeft(knobW));
    mid2Knob.setBounds(area.removeFromLeft(knobW));
    highKnob.setBounds(area);
}
