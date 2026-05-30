// LookAndFeelStudio.h
#pragma once
#include <JuceHeader.h>

using namespace juce;

class LookAndFeelStudio : public LookAndFeel_V4
{
public:
    LookAndFeelStudio()
    {
        // Palette colori
        setColour (ResizableWindow::backgroundColourId, Colour (0xFF0D0D0D));
        setColour (Slider::thumbColourId, Colour (0xFF00E5FF));
        setColour (Slider::trackColourId, Colour (0xFF1A1A1A));
        setColour (Slider::rotarySliderFillColourId, Colour (0xFF00E5FF));
        setColour (Slider::rotarySliderOutlineColourId, Colour (0xFF2A2A2A));
        setColour (Label::textColourId, Colours::white);
        setColour (TextButton::buttonColourId, Colour (0xFF1A1A1A));
        setColour (TextButton::buttonOnColourId, Colour (0xFF00E5FF));
        setColour (TextButton::textColourOnId, Colours::black);
        setColour (TextButton::textColourOffId, Colours::white);
    }

    // -----------------------------
    // SLIDER ROTATIVO (KNOB)
    // -----------------------------
    void drawRotarySlider (Graphics& g, int x, int y, int width, int height,
                           float sliderPos, float rotaryStartAngle, float rotaryEndAngle,
                           Slider& slider) override
    {
        auto radius = jmin (width / 2, height / 2) - 6.0f;
        auto centreX = x + width * 0.5f;
        auto centreY = y + height * 0.5f;
        auto rx = centreX - radius;
        auto ry = centreY - radius;
        auto rw = radius * 2.0f;

        // Sfondo knob
        g.setColour (Colour (0xFF1A1A1A));
        g.fillEllipse (rx, ry, rw, rw);

        // Bordi
        g.setColour (Colour (0xFF2A2A2A));
        g.drawEllipse (rx, ry, rw, rw, 2.0f);

        // Indicatore neon
        auto angle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
        auto pointerLength = radius * 0.75f;
        auto pointerThickness = 3.0f;

        Path p;
        p.addRectangle (-pointerThickness * 0.5f, -radius, pointerThickness, pointerLength);

        g.setColour (Colour (0xFF00E5FF));
        g.fillPath (p, AffineTransform::rotation (angle).translated (centreX, centreY));
    }

    // -----------------------------
    // SLIDER LINEARE
    // -----------------------------
    void drawLinearSlider (Graphics& g, int x, int y, int width, int height,
                           float sliderPos, float minSliderPos, float maxSliderPos,
                           const Slider::SliderStyle style, Slider& slider) override
    {
        auto trackWidth = 6.0f;

        // Track
        g.setColour (Colour (0xFF2A2A2A));
        g.fillRoundedRectangle (x + width * 0.5f - trackWidth * 0.5f, y, trackWidth, height, 3.0f);

        // Thumb neon
        g.setColour (Colour (0xFF00E5FF));
        g.fillRoundedRectangle (x + width * 0.5f - trackWidth * 0.5f, sliderPos - 6, trackWidth, 12, 3.0f);
    }

    // -----------------------------
    // BUTTON
    // -----------------------------
    void drawButtonBackground (Graphics& g, Button& button, const Colour& backgroundColour,
                               bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown) override
    {
        auto bounds = button.getLocalBounds().toFloat();
        auto base = Colour (0xFF1A1A1A);

        if (shouldDrawButtonAsDown)
            base = Colour (0xFF00E5FF);
        else if (shouldDrawButtonAsHighlighted)
            base = Colour (0xFF00AACC);

        g.setColour (base);
        g.fillRoundedRectangle (bounds, 6.0f);
    }

    // -----------------------------
    // LABEL
    // -----------------------------
    void drawLabel (Graphics& g, Label& label) override
    {
        g.fillAll (Colours::transparentBlack);
        g.setColour (Colours::white);
        g.setFont (Font ("Inter", 14.0f, Font::plain));
        g.drawText (label.getText(), label.getLocalBounds(), Justification::centred);
    }
};
