#pragma once

#include <shared_plugin_helpers/shared_plugin_helpers.h>
#include <juce_audio_processors/juce_audio_processors.h>

struct Parameters
{
    void add(juce::AudioProcessor& processor) const
    {
        processor.addParameter(LowCutFreq);
    }

    juce::AudioParameterFloat* LowCutFreq = 
        new juce::AudioParameterFloat({"LowCutFreq", 1}, "Low Cut Frequency", juce::NormalisableRange<float>(20.f, 20000.f, 1.f, 0.25f), 20.f);

    juce::AudioParameterFloat* LowCutQ = 
        new juce::AudioParameterFloat({"LowCutQ", 1}, "Low Cut Quality", juce::NormalisableRange<float>(20.f, 20000.f, 1.f, 0.25f), 20.f);

};