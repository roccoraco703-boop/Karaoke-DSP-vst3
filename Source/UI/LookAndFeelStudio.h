// LookAndFeelStudio.h
#pragma once
#include <JuceHeader.h>

class LookAndFeelStudio : public juce::LookAndFeel_V4
{
public:
    LookAndFeelStudio()
    {
        // Palette colori
        setColour (juce::ResizableWindow::backgroundColourId, juce::Colour (0xFF0D0D0D));
        setColour (juce::Slider::thumbColourId, juce::Colour (0xFF00E5FF));
        setColour (juce::Slider::trackColourId, juce::Colour (0xFF1A1A1A));
        setColour (juce::Slider::rotarySliderFillColourId, juce::Colour (0xFF00E5FF));
        setColour (juce::Slider::rotarySliderOutlineColourId, juce::Colour (0xFF2A2A2A));
        setColour (juce::Label::textColourId, juce::Colours::white);
        setColour (juce::TextButton::buttonColourId, juce::Colour (0xFF1A1A1A));
        setColour (juce::TextButton::buttonOnColourId, juce::Colour (0xFF00E5FF));
        setColour (juce::TextButton::textColourOnId, juce::Colours::black);
        setColour (juce::TextButton::textColourOffId, juce::Colours::white);
    }

    // -----------------------------
    // SLIDER ROTATIVO (KNOB)
    // -----------------------------
    void drawRotarySlider (juce::Graphics& g, int x, int y, int width, int height,
                           float sliderPos, float rotaryStartAngle, float rotaryEndAngle,
                           juce::Slider& slider) override
    {
        auto radius = juce::jmin (width / 2, height / 2) - 8.0f;
        auto centreX = x + width * 0.5f;
        auto centreY = y + height * 0.5f;
        auto rx = centreX - radius;
        auto ry = centreY - radius;
        auto rw = radius * 2.0f;

        // Ombra esterna
        g.setColour (juce::Colour (0x44000000));
        g.fillEllipse (rx + 2, ry + 2, rw, rw);

        // Sfondo knob metallico scuro
        juce::ColourGradient knobGrad (juce::Colour (0xFF333333), centreX - radius, centreY - radius,
                                        juce::Colour (0xFF111111), centreX + radius, centreY + radius, false);
        g.setGradientFill(knobGrad);
        g.fillEllipse (rx, ry, rw, rw);

        // Bordo metallico
        g.setColour (juce::Colour (0xFF555555));
        g.drawEllipse (rx, ry, rw, rw, 1.5f);
        g.setColour (juce::Colour (0xFF1A1A1A));
        g.drawEllipse (rx + 1, ry + 1, rw - 2, rw - 2, 1.0f);

        // Scala tacche sul bordo
        g.setColour (juce::Colour (0xFF666666));
        const int numTicks = 12;
        for (int i = 0; i < numTicks; ++i)
        {
            float t = (float)i / (numTicks - 1);
            float a = rotaryStartAngle + t * (rotaryEndAngle - rotaryStartAngle);
            float x1 = centreX + std::cos(a) * (radius * 0.82f);
            float y1 = centreY + std::sin(a) * (radius * 0.82f);
            float x2 = centreX + std::cos(a) * (radius * 0.92f);
            float y2 = centreY + std::sin(a) * (radius * 0.92f);
            g.drawLine(x1, y1, x2, y2, 1.5f);
        }

        // Indicatore neon
        auto angle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
        auto pointerLength = radius * 0.65f;
        auto pointerThickness = 3.5f;

        juce::Path p;
        p.addRectangle (-pointerThickness * 0.5f, -radius * 0.15f, pointerThickness, pointerLength + radius * 0.15f);

        // Glow
        g.setColour (juce::Colour (0xFF00E5FF).withAlpha(0.4f));
        g.fillPath (p, juce::AffineTransform::rotation (angle).translated (centreX, centreY));
        g.setColour (juce::Colour (0xFF00E5FF));
        g.fillPath (p, juce::AffineTransform::rotation (angle).translated (centreX, centreY));

        // Foro centrale
        g.setColour (juce::Colour (0xFF0D0D0D));
        g.fillEllipse (centreX - 3.5f, centreY - 3.5f, 7.0f, 7.0f);
        g.setColour (juce::Colour (0xFF333333));
        g.drawEllipse (centreX - 3.5f, centreY - 3.5f, 7.0f, 7.0f, 1.0f);
    }

    // -----------------------------
    // SLIDER LINEARE (FADER)
    // -----------------------------
    void drawLinearSlider (juce::Graphics& g, int x, int y, int width, int height,
                           float sliderPos, float minSliderPos, float maxSliderPos,
                           const juce::Slider::SliderStyle style, juce::Slider& slider) override
    {
        auto trackWidth = 4.0f;
        auto thumbW = 24.0f;
        auto thumbH = 14.0f;
        auto trackX = x + width * 0.5f - trackWidth * 0.5f;

        // Track sfondo
        g.setColour (juce::Colour (0xFF1A1A1A));
        g.fillRoundedRectangle (trackX, y, trackWidth, height, 2.0f);

        // Track fill (parte sotto il thumb)
        g.setColour (juce::Colour (0xFF00E5FF).withAlpha(0.4f));
        g.fillRoundedRectangle (trackX, sliderPos, trackWidth, (y + height) - sliderPos, 2.0f);

        // Thumb fader hardware
        auto thumbX = x + width * 0.5f - thumbW * 0.5f;
        auto thumbY = sliderPos - thumbH * 0.5f;
        juce::Rectangle<float> thumbRect(thumbX, thumbY, thumbW, thumbH);

        // Ombra thumb
        g.setColour (juce::Colour (0x44000000));
        g.fillRoundedRectangle (thumbRect.translated(1, 1), 3.0f);

        // Thumb body
        juce::ColourGradient thumbGrad (juce::Colour (0xFF444444), thumbX, thumbY,
                                         juce::Colour (0xFF222222), thumbX + thumbW, thumbY + thumbH, false);
        g.setGradientFill(thumbGrad);
        g.fillRoundedRectangle (thumbRect, 3.0f);

        // Bordo thumb
        g.setColour (juce::Colour (0xFF666666));
        g.drawRoundedRectangle (thumbRect, 3.0f, 1.0f);

        // Linea indicatore sul thumb
        g.setColour (juce::Colour (0xFF00E5FF));
        g.fillRect (thumbX + 6, thumbY + 3, thumbW - 12, thumbH - 6);
    }

    // -----------------------------
    // BUTTON
    // -----------------------------
    void drawButtonBackground (juce::Graphics& g, juce::Button& button, const juce::Colour& backgroundColour,
                               bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown) override
    {
        auto bounds = button.getLocalBounds().toFloat();
        auto base = juce::Colour (0xFF1A1A1A);

        if (button.getToggleState())
            base = juce::Colour (0xFF00E5FF);
        else if (shouldDrawButtonAsDown)
            base = juce::Colour (0xFF0088AA);
        else if (shouldDrawButtonAsHighlighted)
            base = juce::Colour (0xFF2A2A2A);

        g.setColour (base);
        g.fillRoundedRectangle (bounds, 4.0f);

        g.setColour (juce::Colour (0xFF444444));
        g.drawRoundedRectangle (bounds.reduced(1.0f), 4.0f, 1.0f);
    }

    void drawButtonText (juce::Graphics& g, juce::TextButton& button,
                         bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown) override
    {
        auto font = juce::Font(juce::FontOptions(juce::Font::getDefaultSansSerifFontName(), 11.0f, juce::Font::bold));
        g.setFont (font);
        g.setColour (button.getToggleState() ? juce::Colours::black : juce::Colours::white);
        g.drawText (button.getButtonText(), button.getLocalBounds(), juce::Justification::centred, false);
    }

    // -----------------------------
    // LABEL
    // -----------------------------
    void drawLabel (juce::Graphics& g, juce::Label& label) override
    {
        g.fillAll (juce::Colours::transparentBlack);
        g.setColour (juce::Colours::white);
        g.setFont (juce::Font(juce::FontOptions(juce::Font::getDefaultSansSerifFontName(), 12.0f, juce::Font::plain)));
        g.drawText (label.getText(), label.getLocalBounds(), juce::Justification::centred);
    }
};
