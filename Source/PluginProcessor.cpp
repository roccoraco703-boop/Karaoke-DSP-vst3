#include "PluginProcessor.h"
#include <juce_dsp/juce_dsp.h>

KaraokeDSPAudioProcessor::KaraokeDSPAudioProcessor() {}
KaraokeDSPAudioProcessor::~KaraokeDSPAudioProcessor() {}

void KaraokeDSPAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer&)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // simple pass-through (no DSP yet)
}

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new KaraokeDSPAudioProcessor();
}
