#include "DigitalDisplay.h"

DigitalDisplay::DigitalDisplay(const juce::String& parameterName)
    : paramName(parameterName)
{
}

void DigitalDisplay::setValue(const juce::String& text)
{
    if (valueText != text)
    {
        valueText = text;
        repaint();
    }
}

void DigitalDisplay::paint(juce::Graphics& g)
{
    auto bounds = getLocalBounds().toFloat();

    // Sfondo scuro tipo pannello hardware
    g.setColour(juce::Colour(0xFF111111));
    g.fillRoundedRectangle(bounds, 4.0f);

    // Bordo metallico
    g.setColour(juce::Colour(0xFF2A2A2A));
    g.drawRoundedRectangle(bounds.reduced(1.0f), 4.0f, 1.5f);

    // Area display LCD interna
    auto lcdArea = bounds.reduced(6.0f);
    g.setColour(juce::Colour(0xFF0A0A0A));
    g.fillRoundedRectangle(lcdArea, 2.0f);

    // Luce riflessa sotto (effetto vetro)
    juce::ColourGradient glassGrad(juce::Colour(0x10FFFFFF), lcdArea.getX(), lcdArea.getY(),
                                    juce::Colour(0x00FFFFFF), lcdArea.getX(), lcdArea.getY() + lcdArea.getHeight() * 0.4f, false);
    g.setGradientFill(glassGrad);
    g.fillRoundedRectangle(lcdArea, 2.0f);

    // Label parametro in alto a sinistra (piccolo)
    g.setColour(juce::Colour(0xFF00E5FF));
    g.setFont(juce::Font(juce::FontOptions(juce::Font::getDefaultSansSerifFontName(), 11.0f, juce::Font::plain)));
    g.drawText(paramName, lcdArea.removeFromTop(14.0f).toNearestInt(), juce::Justification::centredLeft, true);

    // Valore grande in stile neon
    g.setColour(juce::Colour(0xFF00E5FF));
    g.setFont(juce::Font(juce::FontOptions("Courier New", juce::jmax(14.0f, bounds.getHeight() * 0.35f), juce::Font::bold)));
    g.drawText(valueText, lcdArea.toNearestInt(), juce::Justification::centredRight, true);
}

void DigitalDisplay::resized()
{
}
