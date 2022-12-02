#pragma once

#include <shared_plugin_helpers/shared_plugin_helpers.h>
#include <juce_audio_processors/juce_audio_processors.h>

namespace params
{
    static inline juce::String LOWCUTFREQ = "LowCutFreq";
    static inline juce::String RESONANCE = "LowCutQ";
}

struct Parameters
{
    void setUpParameter(juce::RangedAudioParameter* param, juce::AudioProcessor& processor)
    {
        processor.addParameter(param);

        parametersByName[param->getParameterID()] = param;

    }
    void add(juce::AudioProcessor& processor)
    {
        setUpParameter(LowCutFreq, processor);
        setUpParameter(LowCutQ, processor);
    }

    std::unordered_map<juce::String, juce::RangedAudioParameter*> parametersByName;

    juce::AudioParameterFloat* LowCutFreq = 
        new juce::AudioParameterFloat({params::LOWCUTFREQ, 1}, "Low Cut Frequency", juce::NormalisableRange<float>(20.f, 20000.f, 1.f, 0.25f), 20.f);

    juce::AudioParameterFloat* LowCutQ = 
        new juce::AudioParameterFloat({params::RESONANCE, 1}, "Low Cut Quality", juce::NormalisableRange<float>(0.5f, 12.f), (1.0 / juce::MathConstants<double>::sqrt2));

};