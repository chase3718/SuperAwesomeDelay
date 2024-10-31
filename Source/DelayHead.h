#pragma once
#include <array>
#include <deque>

class DelayHead
{
public:
    DelayHead();
    ~DelayHead();

    void setDelayTime(float delayTime);
    void setGainL(float gainL);
    void setGainR(float gainR);
    void setId(int id);
    void setActive(bool active);

    float getDelayTime() const;
    float getGainL() const;
    float getGainR() const;
    int getId() const;
    bool isActive() const;

    float getSampleForChannel(const std::array<std::deque<float>, 2>& inputBuffer, int channel, int sampleRate) const;

private:
    int id;
    bool active;
    float delayTime;
    float gainL;
    float gainR;
};