#pragma once
#include "Includes.h"
class ITimer {
private:
    bool State = false;
    bool TimerStarted = false;
    int interval;
public:
    template<typename Function>
    void DelayFunction(Function function, int delay);
    int Interval = 200;
    void SetInterval(int interval);
    std::vector<std::function<void()>> Callbacks;

    int IntervalPerTick();
    void AddCallback(std::function<void()> function);
    void Initialize();
    void Start();
    void Stop();
};
