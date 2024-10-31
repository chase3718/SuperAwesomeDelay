#pragma once

#ifndef PARAMS_H
#define PARAMS_H

#include <JuceHeader.h>
#include <vector>
#include <string>

struct DelayHeadParameter {
    std::string name;
    bool active;
    int timeMode;
    float delayTime;
    int beatCount;
    float gainL;
    float gainR;
};

class Params {
public:
    Params();
    ~Params();

    void setGlobalBypass(bool bypass);
    void setGlobalInputGain(float gain);
    void setGlobalOutputGain(float gain);
    void setGlobalTempo(float tempo);

    bool getGlobalBypass() const;
    float getGlobalInputGain() const;
    float getGlobalOutputGain() const;
    float getGlobalTempo() const;

    void addParametersToTree(juce::AudioProcessorValueTreeState& treeState);

    std::vector<DelayHeadParameter>& getDelayHeads();
    const std::vector<DelayHeadParameter>& getDelayHeads() const;

private:
    bool globalBypass;
    float globalInputGain;
    float globalOutputGain;
    float globalTempo;
    std::vector<DelayHeadParameter> delayHeads;
};

#endif // PARAMS_H