#include "TunerComponent.h"

TunerComponent::TunerComponent()
{
    startTimerHz(30); // aggiornamento lancetta
}

void TunerComponent::setPitchData(float frequency, const juce::String& note, float cents)
{
    currentFreq = frequency;
    currentNote = note;
    targetCents = juce::jlimit(-50.0f, 50.0f, cents);
}

void TunerComponent::timerCallback()
{
    // smoothing lancetta
    displayedCents = displayedCents * 0.85f + targetCents * 0.15f;
    repaint();
}

void TunerComponent::paint(juce::Graphics& g)
{
    auto area = getLocalBounds().toFloat();
    g.fillAll(juce::Colours::black);

    // Nota al centro
    g.setColour(juce::Colours::orange);
    g.setFont(juce::Font(juce::FontOptions(juce::Font::getDefaultSansSerifFontName(), 32.0f, juce::Font::bold)));
    g.drawFittedText(currentNote, area.toNearestInt(), juce::Justification::centredTop, 1);

    // Scala cent
    g.setColour(juce::Colours::white);
    g.setFont(juce::Font(juce::FontOptions(juce::Font::getDefaultSansSerifFontName(), 14.0f, juce::Font::plain)));

    auto leftLabelArea = area.removeFromLeft(50).toNearestInt();
    auto rightLabelArea = area.removeFromRight(50).toNearestInt();
    g.drawFittedText(juce::String("-50"), leftLabelArea.getX(), leftLabelArea.getY(), leftLabelArea.getWidth(), leftLabelArea.getHeight(), juce::Justification::centred, 1);
    g.drawFittedText(juce::String("+50"), rightLabelArea.getX(), rightLabelArea.getY(), rightLabelArea.getWidth(), rightLabelArea.getHeight(), juce::Justification::centred, 1);

    // Lancetta
    float angleMin = juce::degreesToRadians(-45.0f);
    float angleMax = juce::degreesToRadians(45.0f);

    float norm = (displayedCents + 50.0f) / 100.0f;
    float angle = angleMin + norm * (angleMax - angleMin);

    auto center = getLocalBounds().getCentre().toFloat();

    float radius = area.getHeight() * 0.4f;

    juce::Path needle;
    needle.startNewSubPath(center.x, center.y);
    needle.lineTo(center.x + std::cos(angle) * radius,
                  center.y + std::sin(angle) * radius);

    // Colore dinamico
    if (std::abs(displayedCents) < 5.0f)
        g.setColour(juce::Colours::green);
    else
        g.setColour(juce::Colours::red);

    g.strokePath(needle, juce::PathStrokeType(3.0f));
}

void TunerComponent::resized()
{
}
