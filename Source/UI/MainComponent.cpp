#include "MainComponent.h"

MainComponent::MainComponent()
{
    // Titolo neon
    titleLabel.setText("KaraokeDSP", juce::dontSendNotification);
    titleLabel.setFont(juce::Font(juce::FontOptions(juce::Font::getDefaultSansSerifFontName(), 28.0f, juce::Font::bold)));
    titleLabel.setColour(juce::Label::textColourId, juce::Colour(0xFF00E5FF));
    addAndMakeVisible(titleLabel);

    statusLabel.setText("Ready", juce::dontSendNotification);
    statusLabel.setFont(juce::Font(juce::FontOptions(juce::Font::getDefaultSansSerifFontName(), 12.0f, juce::Font::plain)));
    statusLabel.setColour(juce::Label::textColourId, juce::Colour(0xFF00E5FF).withAlpha(0.7f));
    addAndMakeVisible(statusLabel);

    bypassButton.setButtonText("BYPASS");
    bypassButton.setClickingTogglesState(true);
    bypassButton.onClick = [this] {
        dspChain.setBypass(bypassButton.getToggleState());
    };
    addAndMakeVisible(bypassButton);

    monitorButton.setButtonText("MONITOR");
    monitorButton.setClickingTogglesState(true);
    monitorButton.onClick = [this] {
        stopAudio();
        startAudio();
    };
    addAndMakeVisible(monitorButton);

    addAndMakeVisible(vuLeft);
    addAndMakeVisible(vuRight);

    addAndMakeVisible(delayDisplay);
    addAndMakeVisible(reverbDisplay);

    addAndMakeVisible(eqSection);

    addAndMakeVisible(ch1);
    addAndMakeVisible(ch2);
    addAndMakeVisible(ch3);

    connectUI();

    setSize(900, 650);

    // Salva il dispositivo di input corrente e avvia audio
    {
        juce::AudioDeviceManager::AudioDeviceSetup setup;
        deviceManager.getAudioDeviceSetup(setup);
        savedInputDevice = setup.inputDeviceName;
    }
    startAudio();

    startTimerHz(30);
}

MainComponent::~MainComponent()
{
    stopAudio();
}

void MainComponent::connectUI()
{
    // EQ knobs → DSP
    eqSection.getLowKnob().onValueChange = [this] {
        dspChain.setPitch((float)eqSection.getLowKnob().getValue());
    };
    eqSection.getMid1Knob().onValueChange = [this] {
        dspChain.setDelay((float)eqSection.getMid1Knob().getValue());
    };
    eqSection.getMid2Knob().onValueChange = [this] {
        dspChain.setReverb((float)eqSection.getMid2Knob().getValue());
    };
    eqSection.getHighKnob().onValueChange = [this] {
        dspChain.setMasterGain((float)eqSection.getHighKnob().getValue());
    };

    // Inizializza i valori
    dspChain.setPitch((float)eqSection.getLowKnob().getValue());
    dspChain.setDelay((float)eqSection.getMid1Knob().getValue());
    dspChain.setReverb((float)eqSection.getMid2Knob().getValue());
    dspChain.setMasterGain((float)eqSection.getHighKnob().getValue());

    // Channel strips → mixer
    ch1.getVolumeSlider().onValueChange = [this] {
        dspChain.setVoiceGain((float)ch1.getVolumeSlider().getValue());
    };
    ch1.getPanSlider().onValueChange = [this] {
        dspChain.setPan((float)ch1.getPanSlider().getValue());
    };
    ch1.getMuteButton().onClick = [this] {
        dspChain.setVoiceMute(ch1.getMuteButton().getToggleState());
    };

    ch2.getVolumeSlider().onValueChange = [this] {
        dspChain.setBaseGain((float)ch2.getVolumeSlider().getValue());
    };
    ch2.getPanSlider().onValueChange = [this] {
        // ch2 pan non mappato direttamente; usa il pan globale di ch1
    };
    ch2.getMuteButton().onClick = [this] {
        dspChain.setBaseMute(ch2.getMuteButton().getToggleState());
    };

    ch3.getVolumeSlider().onValueChange = [this] {
        // Master volume → master gain
        dspChain.setMasterGain((float)ch3.getVolumeSlider().getValue());
    };

    // Inizializza
    dspChain.setVoiceGain((float)ch1.getVolumeSlider().getValue());
    dspChain.setBaseGain((float)ch2.getVolumeSlider().getValue());
    dspChain.setMasterGain((float)ch3.getVolumeSlider().getValue());
    dspChain.setPan((float)ch1.getPanSlider().getValue());
    dspChain.setVoiceMute(ch1.getMuteButton().getToggleState());
    dspChain.setBaseMute(ch2.getMuteButton().getToggleState());
}

void MainComponent::paint(juce::Graphics& g)
{
    // Sfondo scuro metallico
    g.fillAll(juce::Colour(0xFF0D0D0D));

    auto bounds = getLocalBounds().toFloat();

    // Striscia superiore leggermente più chiara
    auto header = bounds.removeFromTop(50);
    g.setColour(juce::Colour(0xFF151515));
    g.fillRect(header);

    // Linea separatrice neon sotto header
    g.setColour(juce::Colour(0xFF00E5FF).withAlpha(0.5f));
    g.fillRect(juce::Rectangle<float>(header.getBottomLeft().x, header.getBottomLeft().y - 1, header.getWidth(), 1.0f));

    // Pannello centrale
    g.setColour(juce::Colour(0xFF111111));
    g.fillRoundedRectangle(bounds.reduced(10), 8.0f);

    // Bordo pannello
    g.setColour(juce::Colour(0xFF2A2A2A));
    g.drawRoundedRectangle(bounds.reduced(10).reduced(0.5f), 8.0f, 1.0f);
}

void MainComponent::resized()
{
    auto area = getLocalBounds().reduced(12);

    // Header
    auto header = area.removeFromTop(40);
    titleLabel.setBounds(header.removeFromLeft(200));
    bypassButton.setBounds(header.removeFromLeft(70));
    monitorButton.setBounds(header.removeFromLeft(70));
    statusLabel.setBounds(header.removeFromRight(100));
    area.removeFromTop(10);

    // Riga superiore: VU meters + display digitali
    auto topRow = area.removeFromTop(220);
    auto vuArea = topRow.removeFromLeft(340);
    vuLeft.setBounds(vuArea.removeFromLeft(vuArea.getWidth() / 2));
    vuRight.setBounds(vuArea);

    topRow.removeFromLeft(20);
    auto displayCol = topRow.removeFromLeft(180);
    delayDisplay.setBounds(displayCol.removeFromTop(60));
    displayCol.removeFromTop(10);
    reverbDisplay.setBounds(displayCol.removeFromTop(60));

    area.removeFromTop(10);

    // EQ section
    eqSection.setBounds(area.removeFromTop(100));

    area.removeFromTop(10);

    // Mixer channels in basso
    auto mixerArea = area;
    int stripW = mixerArea.getWidth() / 3;
    ch1.setBounds(mixerArea.removeFromLeft(stripW));
    ch2.setBounds(mixerArea.removeFromLeft(stripW));
    ch3.setBounds(mixerArea);
}

void MainComponent::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
    dspChain.prepare(sampleRate, samplesPerBlockExpected);
}

void MainComponent::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)
{
    if (bufferToFill.buffer == nullptr || bufferToFill.buffer->getNumChannels() == 0)
        return;

    auto numSamples = bufferToFill.numSamples;
    auto* inL = bufferToFill.buffer->getReadPointer(0, bufferToFill.startSample);
    auto* inR = bufferToFill.buffer->getNumChannels() > 1
                ? bufferToFill.buffer->getReadPointer(1, bufferToFill.startSample)
                : inL;
    auto* outL = bufferToFill.buffer->getWritePointer(0, bufferToFill.startSample);
    auto* outR = bufferToFill.buffer->getNumChannels() > 1
                ? bufferToFill.buffer->getWritePointer(1, bufferToFill.startSample)
                : outL;

    dspChain.process(inL, inR, outL, outR, numSamples);

    // Calcola peak per meters (rms già calcolato in dspChain)
    float leftPeak = 0.0f, rightPeak = 0.0f;
    for (int i = 0; i < numSamples; ++i)
    {
        leftPeak  = std::max(leftPeak,  std::abs(outL[i]));
        rightPeak = std::max(rightPeak,  std::abs(outR[i]));
    }
    outLeftLevel.store(leftPeak);
    outRightLevel.store(rightPeak);
    voiceLevel.store(dspChain.getVoiceRms());
    baseLevel.store(dspChain.getBaseRms());
}

void MainComponent::releaseResources()
{
}

void MainComponent::timerCallback()
{
    // Livelli reali dal DSP
    float left  = outLeftLevel.load();
    float right = outRightLevel.load();
    float voice = voiceLevel.load();
    float base  = baseLevel.load();

    vuLeft.setLevel(left);
    vuRight.setLevel(right);
    ch1.setLevel(voice);
    ch2.setLevel(base);
    ch3.setLevel((left + right) * 0.5f);

    delayDisplay.setValue(juce::String::formatted("%.2f s", (float)eqSection.getMid1Knob().getValue()));
    reverbDisplay.setValue(juce::String::formatted("%.0f %%", (float)eqSection.getMid2Knob().getValue() * 100.0f));

    if (monitorButton.getToggleState())
        statusLabel.setText("MONITOR", juce::dontSendNotification);
    else if (dspChain.isBypassed())
        statusLabel.setText("BYPASS", juce::dontSendNotification);
    else
        statusLabel.setText("DSP Active", juce::dontSendNotification);

    repaint();
}

void MainComponent::startAudio()
{
    juce::AudioDeviceManager::AudioDeviceSetup setup;
    deviceManager.getAudioDeviceSetup(setup);

    if (monitorButton.getToggleState())
    {
        auto monitorName = findMonitorDevice();
        if (monitorName.isNotEmpty())
            setup.inputDeviceName = monitorName;
    }
    else
    {
        setup.inputDeviceName = savedInputDevice;
    }

    deviceManager.initialise(2, 2, nullptr, true, {}, &setup);
    deviceManager.addAudioCallback(reinterpret_cast<juce::AudioIODeviceCallback*>(this));
}

void MainComponent::stopAudio()
{
    deviceManager.removeAudioCallback(reinterpret_cast<juce::AudioIODeviceCallback*>(this));
    deviceManager.closeAudioDevice();
}

juce::String MainComponent::findMonitorDevice()
{
    for (auto* deviceType : deviceManager.getAvailableDeviceTypes())
    {
        auto names = deviceType->getDeviceNames(true);
        for (const auto& name : names)
        {
            if (name.containsIgnoreCase("Monitor"))
                return name;
        }
    }
    return {};
}
