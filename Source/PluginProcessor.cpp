#include "PluginProcessor.h"
#include "PluginEditor.h"
#include <juce_dsp/juce_dsp.h>

NewPluginTemplateAudioProcessor::NewPluginTemplateAudioProcessor()
{
    parameters.add(*this);
}

void NewPluginTemplateAudioProcessor::processBlock(juce::AudioBuffer<float>& buffer,
                                                   juce::MidiBuffer& midiMessages)

{
    juce::ignoreUnused(midiMessages);

    auto block = juce::dsp::AudioBlock<float>(buffer);

    for (int c = 0; c < block.getNumChannels(); c++){

        auto singleChannel = block.getSingleChannelBlock(c);
        
        auto ctx = juce::dsp::ProcessContextReplacing(singleChannel);

        if(c == 0){
            lowCutR.process(ctx);
        }

        else{
            lowCutL.process(ctx);
        }
    }

}

juce::AudioProcessorEditor* NewPluginTemplateAudioProcessor::createEditor()
{
    return new NewPluginTemplateAudioProcessorEditor(*this);
}

// Will do before playback
void NewPluginTemplateAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    juce::dsp::ProcessSpec spec;

    spec.sampleRate = sampleRate;
    spec.maximumBlockSize = samplesPerBlock;
    spec.numChannels = 2;

    lowCutR.prepare(spec);

    lowCutR.reset();

    lowCutR.parameters->setCutOffFrequency(sampleRate, 500.f);

    lowCutL.prepare(spec);

    lowCutL.reset();

    lowCutL.parameters->setCutOffFrequency(sampleRate, 500.f);

}

void NewPluginTemplateAudioProcessor::getStateInformation(juce::MemoryBlock& destData)
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

void NewPluginTemplateAudioProcessor::setStateInformation(const void* data,
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
    return new NewPluginTemplateAudioProcessor();
}
