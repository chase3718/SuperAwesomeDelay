/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SuperAwesomeDelayAudioProcessorEditor::SuperAwesomeDelayAudioProcessorEditor(SuperAwesomeDelayAudioProcessor& p)
    : AudioProcessorEditor(&p), audioProcessor(p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize(1000, 800);
}

SuperAwesomeDelayAudioProcessorEditor::~SuperAwesomeDelayAudioProcessorEditor()
{
}

//==============================================================================
void SuperAwesomeDelayAudioProcessorEditor::paint(juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
}

void SuperAwesomeDelayAudioProcessorEditor::resized()
{
}

void SuperAwesomeDelayAudioProcessorEditor::sliderValueChanged(juce::Slider* slider) {

}