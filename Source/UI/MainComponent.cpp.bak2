#include "MainComponent.h"

MainComponent::MainComponent()
{
    addAndMakeVisible(pitchKnob);
    pitchKnob.setRange(-12.0, 12.0, 0.1);
    pitchKnob.setValue(0.0);

    addAndMakeVisible(delayKnob);
    delayKnob.setRange(0.0, 1.0, 0.01);
    delayKnob.setValue(0.3);

    addAndMakeVisible(reverbKnob);
    reverbKnob.setRange(0.0, 1.0, 0.01);
    reverbKnob.setValue(0.3);

    addAndMakeVisible(vu);

    setSize(600, 400);

    startTimerHz(30);
}

MainComponent::~MainComponent()
{
}

void MainComponent::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colours::black);

    g.setColour(juce::Colours::white);
    g.setFont(20.0f);
    g.drawText("Karaoke DSP Console", getLocalBounds().removeFromTop(40),
               juce::Justification::centred);
}

void MainComponent::resized()
{
    auto area = getLocalBounds().reduced(20);

    auto top = area.removeFromTop(100);
    pitchKnob.setBounds(top.removeFromLeft(150));
    delayKnob.setBounds(top.removeFromLeft(150));
    reverbKnob.setBounds(top.removeFromLeft(150));

    vu.setBounds(area.removeFromBottom(200));
}

void MainComponent::timerCallback()
{
    repaint();
}
