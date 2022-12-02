#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "Parameters.h"

SimpleEQAudioProcessorEditor::SimpleEQAudioProcessorEditor(
    SimpleEQAudioProcessor& p)
    : AudioProcessorEditor(&p),
    cutOff(),
    cutOffAttachment(p.getParameterById(params::LOWCUTFREQ), cutOff)
{
    setSize(400, 300);
    addAndMakeVisible(cutOff);
}

void SimpleEQAudioProcessorEditor::paint(juce::Graphics& g)
{
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
}

void SimpleEQAudioProcessorEditor::resized()
{
    cutOff.setBounds(10,10, getWidth()*0.9, 20);
}
