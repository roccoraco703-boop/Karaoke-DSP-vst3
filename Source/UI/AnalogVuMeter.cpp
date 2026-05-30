#include "AnalogVuMeter.h"

AnalogVuMeter::AnalogVuMeter()
{
    startTimerHz(60);
}

void AnalogVuMeter::setLevel(float newLevel)
{
    level = juce::jlimit(0.0f, 1.0f, newLevel);
}

void AnalogVuMeter::timerCallback()
{
    smoothLevel = smoothLevel * 0.85f + level * 0.15f;
    if (std::abs(smoothLevel - level) > 0.001f)
        repaint();
}

void AnalogVuMeter::paint(juce::Graphics& g)
{
    auto bounds = getLocalBounds().toFloat();
    auto centre = bounds.getCentre();
    auto radius = juce::jmin(bounds.getWidth(), bounds.getHeight()) * 0.5f - 4.0f;

    // Sfondo scuro della console
    g.fillAll(juce::Colours::transparentBlack);

    // Cornice metallica scura
    g.setColour(juce::Colour(0xFF1A1A1A));
    g.fillEllipse(centre.x - radius - 2, centre.y - radius - 2, (radius + 2) * 2, (radius + 2) * 2);

    // Sfondo quadrante con gradiente vintage
    juce::ColourGradient bgGrad(juce::Colour(0xFFFFD700), centre.x, centre.y - radius * 0.5f,
                                   juce::Colour(0xFFFF8C00), centre.x, centre.y + radius, true);
    g.setGradientFill(bgGrad);
    g.fillEllipse(centre.x - radius, centre.y - radius, radius * 2, radius * 2);

    // Ombra interna
    g.setColour(juce::Colour(0x22000000));
    g.drawEllipse(centre.x - radius + 4, centre.y - radius + 4, (radius - 4) * 2, (radius - 4) * 2, 2.0f);

    // Scala con tacche
    g.setColour(juce::Colours::black);
    const int numTicks = 21;
    for (int i = 0; i < numTicks; ++i)
    {
        float norm = (float)i / (numTicks - 1);
        float angle = startAngle + norm * (endAngle - startAngle);
        float x1 = centre.x + std::cos(angle) * (radius * 0.78f);
        float y1 = centre.y + std::sin(angle) * (radius * 0.78f);
        float x2 = centre.x + std::cos(angle) * (radius * 0.88f);
        float y2 = centre.y + std::sin(angle) * (radius * 0.88f);
        g.drawLine(x1, y1, x2, y2, (i % 5 == 0) ? 2.5f : 1.0f);
    }

    // Numeri scala
    g.setFont(juce::Font(juce::FontOptions(juce::Font::getDefaultSansSerifFontName(), radius * 0.18f, juce::Font::bold)));
    const char* labels[] = {"-20", "-10", "-7", "-5", "-3", "0", "+1", "+2", "+3"};
    const float labelNorms[] = {0.0f, 0.25f, 0.375f, 0.45f, 0.55f, 0.75f, 0.85f, 0.925f, 1.0f};
    for (int i = 0; i < 9; ++i)
    {
        float angle = startAngle + labelNorms[i] * (endAngle - startAngle);
        float x = centre.x + std::cos(angle) * (radius * 0.62f);
        float y = centre.y + std::sin(angle) * (radius * 0.62f);
        g.drawSingleLineText(labels[i], (int)x, (int)y, juce::Justification::centred);
    }

    // Label VU
    g.setFont(juce::Font(juce::FontOptions(juce::Font::getDefaultSansSerifFontName(), radius * 0.22f, juce::Font::bold)));
    g.drawSingleLineText("VU", (int)centre.x, (int)(centre.y + radius * 0.35f), juce::Justification::centred);

    // Ago
    float norm = juce::jlimit(0.0f, 1.0f, smoothLevel);
    float angle = startAngle + norm * (endAngle - startAngle);
    float needleLen = radius * 0.72f;
    float tipX = centre.x + std::cos(angle) * needleLen;
    float tipY = centre.y + std::sin(angle) * needleLen;

    juce::Path needle;
    needle.startNewSubPath(centre.x, centre.y);
    needle.lineTo(tipX, tipY);

    // Colore ago: rosso sopra +2
    if (norm > 0.925f)
        g.setColour(juce::Colours::red);
    else
        g.setColour(juce::Colours::black);

    g.strokePath(needle, juce::PathStrokeType(2.5f, juce::PathStrokeType::curved, juce::PathStrokeType::rounded));

    // Foro centrale
    g.setColour(juce::Colour(0xFF0D0D0D));
    g.fillEllipse(centre.x - 4, centre.y - 4, 8, 8);
    g.setColour(juce::Colour(0xFF333333));
    g.drawEllipse(centre.x - 4, centre.y - 4, 8, 8, 1.0f);
}

void AnalogVuMeter::resized()
{
}
