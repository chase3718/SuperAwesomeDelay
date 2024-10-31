/*
  ==============================================================================

	This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include <cmath>
#include <iostream>
#include <thread>
#include <vector>

juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout()
{
	juce::AudioProcessorValueTreeState::ParameterLayout layout;

	return layout;
}


//==============================================================================
std::array<std::deque<float>, 2> inputBuffer;

SuperAwesomeDelayAudioProcessor::SuperAwesomeDelayAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
: AudioProcessor(BusesProperties()
#if !JucePlugin_IsMidiEffect
#if !JucePlugin_IsSynth
		.withInput("Input", juce::AudioChannelSet::stereo(), true)
#endif
		.withOutput("Output", juce::AudioChannelSet::stereo(), true)
#endif
	),
	treeState(*this, nullptr),
	params()
#endif
{
	//addParametersToTree();
	inputGain = 1.0f;
	outputGain = 1.0f;
}

SuperAwesomeDelayAudioProcessor::~SuperAwesomeDelayAudioProcessor()
{
}

//==============================================================================
const juce::String SuperAwesomeDelayAudioProcessor::getName() const
{
	return JucePlugin_Name;
}

bool SuperAwesomeDelayAudioProcessor::acceptsMidi() const
{
#if JucePlugin_WantsMidiInput
	return true;
#else
	return false;
#endif
}

bool SuperAwesomeDelayAudioProcessor::producesMidi() const
{
#if JucePlugin_ProducesMidiOutput
	return true;
#else
	return false;
#endif
}

bool SuperAwesomeDelayAudioProcessor::isMidiEffect() const
{
#if JucePlugin_IsMidiEffect
	return true;
#else
	return false;
#endif
}

double SuperAwesomeDelayAudioProcessor::getTailLengthSeconds() const
{
	return 0.0;
}

int SuperAwesomeDelayAudioProcessor::getNumPrograms()
{
	return 1; // NB: some hosts don't cope very well if you tell them there are 0 programs,
	// so this should be at least 1, even if you're not really implementing programs.
}

int SuperAwesomeDelayAudioProcessor::getCurrentProgram()
{
	return 0;
}

void SuperAwesomeDelayAudioProcessor::setCurrentProgram(int index)
{
}

const juce::String SuperAwesomeDelayAudioProcessor::getProgramName(int index)
{
	return {};
}

void SuperAwesomeDelayAudioProcessor::changeProgramName(int index, const juce::String& newName)
{
}

//==============================================================================
void SuperAwesomeDelayAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
	// Use this method as the place to do any pre-playback
	// initialisation that you need..
	this->sampleRate = sampleRate;

}

void SuperAwesomeDelayAudioProcessor::releaseResources()
{
	// When playback stops, you can use this as an opportunity to free up any
	// spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool SuperAwesomeDelayAudioProcessor::isBusesLayoutSupported(const BusesLayout& layouts) const
{
#if JucePlugin_IsMidiEffect
	juce::ignoreUnused(layouts);
	return true;
#else
	// This is the place where you check if the layout is supported.
	// In this template code we only support mono or stereo.
	// Some plugin hosts, such as certain GarageBand versions, will only
	// load plugins that support stereo bus layouts.
	if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono() && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
		return false;

	// This checks if the input layout matches the output layout
#if !JucePlugin_IsSynth
	if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
		return false;
#endif

	return true;
#endif
}
#endif

void SuperAwesomeDelayAudioProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
	// Initialize the input buffer with 10 seconds worth of silent samples on two channels
	if (inputBuffer[0].size() == 0) {
		inputBuffer = {
			std::deque<float>(sampleRate * 10, 0.0f),
			std::deque<float>(sampleRate * 10, 0.0f)
		};
	}

	juce::ScopedNoDenormals noDenormals;
	int totalNumInputChannels = getTotalNumInputChannels();
	int totalNumOutputChannels = getTotalNumOutputChannels();

	for (int i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
		buffer.clear(i, 0, buffer.getNumSamples());

	auto processChannel = [&](int channel) {
		auto* channelData = buffer.getWritePointer(channel);
		for (int i = 0; i < buffer.getNumSamples(); ++i) {
			float inputSample = channelData[i] * this->inputGain;

			inputBuffer[channel].push_back(inputSample);
			inputBuffer[channel].pop_front();

			float wetSample = 0.0f;
			float drySample = inputSample;

			// Process the delay heads
			for (int j = 0; j < 16; j++) {
				DelayHead& delayHead = delayHeads[j];
				if (!delayHead.isActive())
					continue;

				wetSample += delayHead.getSampleForChannel(inputBuffer, channel, sampleRate);
			}

			channelData[i] = (wetSample + drySample) * this->outputGain;
		}
		};

	std::vector<std::thread> threads;
	for (int channel = 0; channel < totalNumInputChannels; channel++) {
		threads.emplace_back(processChannel, channel);
	}

	for (auto& thread : threads) {
		thread.join();
	}
}
//==============================================================================
bool SuperAwesomeDelayAudioProcessor::hasEditor() const
{
	return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* SuperAwesomeDelayAudioProcessor::createEditor()
{
	return new SuperAwesomeDelayAudioProcessorEditor(*this);
}

//==============================================================================
void SuperAwesomeDelayAudioProcessor::getStateInformation(juce::MemoryBlock& destData)
{
	// You should use this method to store your parameters in the memory block.
	// You could do that either as raw data, or use the XML or ValueTree classes
	// as intermediaries to make it easy to save and load complex data.
}

void SuperAwesomeDelayAudioProcessor::setStateInformation(const void* data, int sizeInBytes)
{
	// You should use this method to restore your parameters from this memory block,
	// whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
	return new SuperAwesomeDelayAudioProcessor();
}


