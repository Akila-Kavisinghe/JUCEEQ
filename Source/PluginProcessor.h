#pragma once

#include "Parameters.h"

#include <juce_dsp/juce_dsp.h>

class SimpleEQAudioProcessor : public PluginHelpers::ProcessorBase
{
    using Filter = juce::dsp::StateVariableFilter::Filter<float>;

public:
    SimpleEQAudioProcessor();

    void processBlock(juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    juce::AudioProcessorEditor* createEditor() override;

    void getStateInformation(juce::MemoryBlock& destData) override;
    void setStateInformation(const void* data, int sizeInBytes) override;

    void prepareToPlay(double sampleRate, int samplesPerBlock) override;

    juce::RangedAudioParameter& getParameterById(const juce::String& id) const;

private:

    Parameters parameters;

    std::array<Filter, 2> filters;

    juce::dsp::ProcessSpec spec;

    

};
