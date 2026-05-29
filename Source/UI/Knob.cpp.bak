#include "Knob.h"

Knob::Knob(const juce::String& labelText)
{
    // Slider stile rotativo
    slider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    slider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    slider.setRange(0.0, 1.0, 0.01);
    slider.setValue(0.5);
    slider.setColour(juce::Slider::rotarySliderFillColourId, juce::Colours::orange);
    slider.setColour(juce::Slider::rotarySliderOutlineColourId, juce::Colours::darkgrey);
    addAndMakeVisible(slider);

    // Etichetta
    label.setText(labelText, juce::dontSendNotification);
    label.setJustificationType(juce::Justification::centred);
    label.setColour(juce::Label::textColourId, juce::Colours::white);
    label.setFont(juce::Font(juce::FontOptions(juce::Font::getDefaultSansSerifFontName(), 14.0f, juce::Font::plain)));
    addAndMakeVisible(label);
}

void Knob::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colours::transparentBlack);
}

void Knob::resized()
{
    auto area = getLocalBounds();
    label.setBounds(area.removeFromBottom(20));
    slider.setBounds(area);
}

void Knob::setRange(double min, double max, double step)
{
    slider.setRange(min, max, step);
}

void Knob::setValue(double newValue)
{
    slider.setValue(newValue);
}

double Knob::getValue() const
{
    return slider.getValue();
}
