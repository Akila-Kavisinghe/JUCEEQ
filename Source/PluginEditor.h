#pragma once

#include "PluginProcessor.h"

class SimpleEQAudioProcessorEditor : public juce::AudioProcessorEditor
{
public:
    explicit SimpleEQAudioProcessorEditor(SimpleEQAudioProcessor&);

private:
    void paint(juce::Graphics&) override;
    void resized() override;

    juce::Slider cutOff;

    juce::SliderParameterAttachment cutOffAttachment;

};
