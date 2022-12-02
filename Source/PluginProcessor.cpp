#include "PluginProcessor.h"
#include "PluginEditor.h"
#include <juce_dsp/juce_dsp.h>

SimpleEQAudioProcessor::SimpleEQAudioProcessor()
{
    parameters.add(*this);
}

void SimpleEQAudioProcessor::processBlock(juce::AudioBuffer<float>& buffer,
                                                   juce::MidiBuffer& midiMessages)

{
    juce::ignoreUnused(midiMessages);

    auto lowCut = parameters.LowCutFreq->get();
    auto lowCutQ = parameters.LowCutQ->get();

    auto block = juce::dsp::AudioBlock<float>(buffer);

    for (int c = 0; c < block.getNumChannels(); c++){

        auto singleChannel = block.getSingleChannelBlock(c);
        
        auto ctx = juce::dsp::ProcessContextReplacing(singleChannel);

        filters[c].parameters->setCutOffFrequency(spec.sampleRate, lowCut, lowCutQ);

        filters[c].process(ctx);

    }

}

juce::AudioProcessorEditor* SimpleEQAudioProcessor::createEditor()
{
    return new SimpleEQAudioProcessorEditor(*this);
}

// Will do before playback
void SimpleEQAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    
    spec.sampleRate = sampleRate;
    spec.maximumBlockSize = samplesPerBlock;
    spec.numChannels = 2;

    for (int c = 0; c < spec.numChannels; c++){

        filters[c].prepare(spec);
        filters[c].reset();
        filters[c].parameters->setCutOffFrequency(sampleRate, 500.f);

    }
 
}

void SimpleEQAudioProcessor::getStateInformation(juce::MemoryBlock& destData)
{
    //Serializes your parameters, and any other potential data into an XML:

    juce::ValueTree params("Params");

    for (auto& param: getParameters())
    {
        juce::ValueTree paramTree(PluginHelpers::getParamID(param));
        paramTree.setProperty("Value", param->getValue(), nullptr);
        params.appendChild(paramTree, nullptr);
    }

    juce::ValueTree pluginPreset("MyPlugin");
    pluginPreset.appendChild(params, nullptr);
    //This a good place to add any non-parameters to your preset

    copyXmlToBinary(*pluginPreset.createXml(), destData);
}

void SimpleEQAudioProcessor::setStateInformation(const void* data,
                                                          int sizeInBytes)
{
    //Loads your parameters, and any other potential data from an XML:

    auto xml = getXmlFromBinary(data, sizeInBytes);

    if (xml != nullptr)
    {
        auto preset = juce::ValueTree::fromXml(*xml);
        auto params = preset.getChildWithName("Params");

        for (auto& param: getParameters())
        {
            auto paramTree = params.getChildWithName(PluginHelpers::getParamID(param));

            if (paramTree.isValid())
                param->setValueNotifyingHost(paramTree["Value"]);
        }

        //Load your non-parameter data now
    }
}

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new SimpleEQAudioProcessor();
}

juce::RangedAudioParameter& SimpleEQAudioProcessor::getParameterById(const juce::String& id) const
{
    auto result = parameters.parametersByName.at(id);

    return *result;

}
