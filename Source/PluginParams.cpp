#include "PluginParams.h"

Params::Params()
    : globalBypass(false), globalInputGain(1.0f), globalOutputGain(1.0f), globalTempo(120.0f)
{
    // Initialize 16 delay heads with default values
    for (int i = 0; i < 16; ++i) {
        delayHeads.push_back({
            "DelayHead" + std::to_string(i),
            false, // active
            0,     // timeMode
            0.0f,  // delayTime
            0,     // beatCount
            0.0f,  // gainL
            0.0f   // gainR
            });
    }
}

Params::~Params() {
}

void Params::setGlobalBypass(bool bypass) {
    globalBypass = bypass;
}

void Params::setGlobalInputGain(float gain) {
    globalInputGain = gain;
}

void Params::setGlobalOutputGain(float gain) {
    globalOutputGain = gain;
}

void Params::setGlobalTempo(float tempo) {
    globalTempo = tempo;
}

bool Params::getGlobalBypass() const {
    return globalBypass;
}

float Params::getGlobalInputGain() const {
    return globalInputGain;
}

float Params::getGlobalOutputGain() const {
    return globalOutputGain;
}

float Params::getGlobalTempo() const {
    return globalTempo;
}

std::vector<DelayHeadParameter>& Params::getDelayHeads() {
    return delayHeads;
}

const std::vector<DelayHeadParameter>& Params::getDelayHeads() const {
    return delayHeads;
}

void Params::addParametersToTree(juce::AudioProcessorValueTreeState& treeState) {
    treeState.createAndAddParameter("globalBypass", "Bypass", "Bypass", juce::NormalisableRange<float>(0.0f, 1.0f, 1.0f), 0.0f, nullptr, nullptr);
    treeState.createAndAddParameter("globalInputGain", "Input Gain", "Input Gain", juce::NormalisableRange<float>(0.0f, 1.5f, 0.01f), 1.0f, nullptr, nullptr);
    treeState.createAndAddParameter("globalOutputGain", "Output Gain", "Output Gain", juce::NormalisableRange<float>(0.0f, 1.5f, 0.01f), 1.0f, nullptr, nullptr);
    treeState.createAndAddParameter("globalTempo", "Tempo", "Tempo", juce::NormalisableRange<float>(60.0f, 240.0f, 1.0f), 120.0f, nullptr, nullptr);

    for (int i = 0; i < 16; i++) {
        treeState.createAndAddParameter("delayHead" + std::to_string(i) + "Active", "Active", "Active", juce::NormalisableRange<float>(0.0f, 1.0f, 1.0f), 0.0f, nullptr, nullptr);
        treeState.createAndAddParameter("delayHead" + std::to_string(i) + "TimeMode", "Time Mode", "Time Mode", juce::NormalisableRange<float>(0.0f, 1.0f, 1.0f), 0.0f, nullptr, nullptr);
        treeState.createAndAddParameter("delayHead" + std::to_string(i) + "DelayTime", "Delay Time", "Delay Time", juce::NormalisableRange<float>(0.0f, 1.0f, 0.01f), 0.0f, nullptr, nullptr);
        treeState.createAndAddParameter("delayHead" + std::to_string(i) + "BeatCount", "Beat Count", "Beat Count", juce::NormalisableRange<float>(0.0f, 1.0f, 1.0f), 0.0f, nullptr, nullptr);
        treeState.createAndAddParameter("delayHead" + std::to_string(i) + "GainL", "Gain L", "Gain L", juce::NormalisableRange<float>(0.0f, 1.0f, 0.01f), 0.0f, nullptr, nullptr);
        treeState.createAndAddParameter("delayHead" + std::to_string(i) + "GainR", "Gain R", "Gain R", juce::NormalisableRange<float>(0.0f, 1.0f, 0.01f), 0.0f, nullptr, nullptr);
    }
}