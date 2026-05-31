#pragma once
#include <juce_audio_utils/juce_audio_utils.h>
#include <juce_gui_basics/juce_gui_basics.h>

#include "AnalogVuMeter.h"
#include "DigitalDisplay.h"
#include "EqualizerSection.h"
#include "ChannelStrip.h"
#include "../DSP/DSPChain.h"

class MainComponent : public juce::AudioAppComponent,
                      public juce::Timer
{
public:
    MainComponent();
    ~MainComponent() override;

    void paint(juce::Graphics&) override;
    void resized() override;
    void timerCallback() override;

    // AudioAppComponent callbacks
    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;

private:
    // Titolo
    juce::Label titleLabel;
    juce::Label statusLabel;
    juce::TextButton bypassButton;
    juce::TextButton monitorButton;

    // VU meters vintage
    AnalogVuMeter vuLeft;
    AnalogVuMeter vuRight;

    // Display digitali Delay / Reverb
    DigitalDisplay delayDisplay{"DELAY"};
    DigitalDisplay reverbDisplay{"REVERB"};

    // EQ
    EqualizerSection eqSection;

    // Mixer channels
    ChannelStrip ch1{"VOCAL"};
    ChannelStrip ch2{"BACKING"};
    ChannelStrip ch3{"MASTER"};

    // DSP
    DSPChain dspChain;

    // Livelli audio reali
    std::atomic<float> outLeftLevel{ 0.0f };
    std::atomic<float> outRightLevel{ 0.0f };
    std::atomic<float> voiceLevel{ 0.0f };
    std::atomic<float> baseLevel{ 0.0f };

    // Dispositivo audio
    juce::String savedInputDevice;
    juce::ComboBox inputSelector;
    juce::Label inputLabel;

    void connectUI();
    void startAudio();
    void stopAudio();
    void refreshInputDevices();

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainComponent)
};
