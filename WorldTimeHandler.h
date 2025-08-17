#pragma once

#include <chrono>

class WTH
{
public:
	static void UpdateTime(){
		auto now = std::chrono::high_resolution_clock::now();
		float seconds = std::chrono::duration<float>(now.time_since_epoch()).count();

		last_deltaTime = seconds - last_time;
		last_time = seconds;
	}

	static inline int DeltaTimeMS() { return static_cast<int>(last_deltaTime * 1000); }
	static inline double DeltaTimeSec() { return last_deltaTime; }

private:
	static double last_time;
	static double last_deltaTime;
};

double WTH::last_time = 0.0f;
double WTH::last_deltaTime = 0.0f;

