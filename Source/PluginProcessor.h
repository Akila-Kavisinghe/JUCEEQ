#pragma once

#include "Parameters.h"

#include <juce_dsp/juce_dsp.h>

class NewPluginTemplateAudioProcessor : public PluginHelpers::ProcessorBase
{
public:
    NewPluginTemplateAudioProcessor();

    void processBlock(juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    juce::AudioProcessorEditor* createEditor() override;

    void getStateInformation(juce::MemoryBlock& destData) override;
    void setStateInformation(const void* data, int sizeInBytes) override;

    void prepareToPlay(double sampleRate, int samplesPerBlock) override;

private:

    Parameters parameters;

    juce::dsp::StateVariableFilter::Filter<float> lowCutR;

    juce::dsp::StateVariableFilter::Filter<float> lowCutL;

};
