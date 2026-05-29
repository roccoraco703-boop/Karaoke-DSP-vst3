#pragma once
#include <juce_core/juce_core.h>
#include <juce_events/juce_events.h>
#include <juce_graphics/juce_graphics.h>
#include <juce_gui_basics/juce_gui_basics.h>
#include <juce_audio_utils/juce_audio_utils.h>

class TunerComponent : public juce::Component,
                       private juce::Timer
{
public:
    TunerComponent();
    ~TunerComponent() override = default;

    void paint(juce::Graphics&) override;
    void resized() override;

    // Aggiornamento dati dal DSP
    void setPitchData(float frequency, const juce::String& note, float cents);

private:
    void timerCallback() override;

    float currentFreq = 0.0f;
    float displayedCents = 0.0f;   // valore smussato
    float targetCents = 0.0f;

    juce::String currentNote = "---";

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(TunerComponent)
};
