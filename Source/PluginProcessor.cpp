#include "PluginProcessor.h"
#include <juce_dsp/juce_dsp.h>

KaraokeDSPAudioProcessor::KaraokeDSPAudioProcessor() {}
KaraokeDSPAudioProcessor::~KaraokeDSPAudioProcessor() {}

void KaraokeDSPAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    dspChain.prepare(sampleRate, samplesPerBlock);
}

void KaraokeDSPAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer&)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    auto* inL = buffer.getReadPointer(0);
    auto* inR = totalNumInputChannels > 1 ? buffer.getReadPointer(1) : inL;
    auto* outL = buffer.getWritePointer(0);
    auto* outR = totalNumOutputChannels > 1 ? buffer.getWritePointer(1) : outL;

    dspChain.process(inL, inR, outL, outR, buffer.getNumSamples());
}

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new KaraokeDSPAudioProcessor();
}
