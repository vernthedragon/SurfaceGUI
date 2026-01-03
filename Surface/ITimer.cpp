#include "ITimer.h"


template<typename Function>
void ITimer::DelayFunction(Function function, int delay) {
    std::thread t([=]() {
        std::this_thread::sleep_for(std::chrono::milliseconds(delay));
        function();
        });
}

int Interval = 200;
void ITimer::SetInterval(int interval) {
    Interval = interval;
}



void ITimer::AddCallback(std::function<void()> function) {
    Callbacks.push_back(function);
}
void ITimer::Initialize() {
    if (!TimerStarted && !State)
        return;
    std::thread t([=]() {
        while (true) {
            if (!this->State) return;
            std::this_thread::sleep_for(std::chrono::milliseconds(Interval));
            for (auto Callback : Callbacks)
            {
                Callback();
            }
            TimerStarted = true;
        }
        });
    t.detach();
    TimerStarted = false;
}
int ITimer::IntervalPerTick() {
    return Interval;
}
void ITimer::Start() {
    State = true;
}
void ITimer::Stop() {
    State = false;
}