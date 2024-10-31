#include "DelayHead.h"

DelayHead::DelayHead() : id(0), active(false), delayTime(0.0f), gainL(0.0f), gainR(0.0f)
{
}

DelayHead::~DelayHead()
{
}

void DelayHead::setId(int id)
{
    this->id = id;
}

void DelayHead::setActive(bool active)
{
    this->active = active;
}

int DelayHead::getId() const
{
    return id;
}

bool DelayHead::isActive() const
{
    return active;
}

void DelayHead::setDelayTime(float delayTime)
{
    this->delayTime = delayTime;
}

void DelayHead::setGainL(float gainL)
{
    this->gainL = gainL;
}

void DelayHead::setGainR(float gainR)
{
    this->gainR = gainR;
}

float DelayHead::getDelayTime() const
{
    return delayTime;
}

float DelayHead::getGainL() const
{
    return gainL;
}

float DelayHead::getGainR() const
{
    return gainR;
}

float DelayHead::getSampleForChannel(const std::array<std::deque<float>, 2>& inputBuffer, int channel, int sampleRate) const
{
    float sample = 0.0f;
    int delaySamples = static_cast<int>(this->delayTime * sampleRate);
    if (delaySamples < inputBuffer[channel].size()) {
        float delayedSample = inputBuffer[channel].at(inputBuffer[channel].size() - delaySamples - 1);
        sample = delayedSample  ;
    }

    return sample;
}