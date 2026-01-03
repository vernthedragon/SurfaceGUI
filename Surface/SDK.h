#pragma once
#include "ITimer.h"
#define GLOBAL_TICK_PER_SECOND 50
#define GLOBAL_TIME_INTERVAL (1000 / GLOBAL_TICK_PER_SECOND)
#define TICK_TO_TIME(x, t) (t.IntervalPerTick() * x)
#define TIME_TO_TICK(x, t) (x / t.IntervalPerTick())
class GlobalVariables {
public:
	int TickCount;
	float RealTime;
};
class SDK {
public:
	SDK() {
		GlobalTimer.SetInterval(GLOBAL_TIME_INTERVAL); GlobalTimer.Start(); GlobalTimer.Initialize(); GlobalTimer.AddCallback([&]() {Vars.TickCount++; Vars.RealTime = TICK_TO_TIME(Vars.TickCount, GlobalTimer); });
	}
	GlobalVariables Vars;
	ITimer GlobalTimer;
};