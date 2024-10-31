#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include <array> // Include the array header

struct DelayHeadSliders {
    juce::TextEditor name;
    juce::Slider active;
    juce::Slider timeMode;
    juce::Slider delayTime;
    juce::Slider beatCount;
    juce::Slider gainL;
    juce::Slider gainR;
};

class SuperAwesomeDelayAudioProcessorEditor : public juce::AudioProcessorEditor,
    public juce::Slider::Listener
{
public:
    SuperAwesomeDelayAudioProcessorEditor(SuperAwesomeDelayAudioProcessor&);
    ~SuperAwesomeDelayAudioProcessorEditor() override;

    //==============================================================================
    void paint(juce::Graphics&) override;
    void resized() override;
    void sliderValueChanged(juce::Slider* slider) override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    SuperAwesomeDelayAudioProcessor& audioProcessor;
    juce::Slider inputGainSlider;
    juce::Slider outputGainSlider;

    std::array<DelayHeadSliders, 16> delayHeads;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SuperAwesomeDelayAudioProcessorEditor)
};