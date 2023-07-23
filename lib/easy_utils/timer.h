//
// Created by rohandev on 7/23/23.
//

#ifndef TREELINE_TEST_TIMER_H
#define TREELINE_TEST_TIMER_H

#include <cstdint>
#include <atomic>
#include <pthread.h>

class timer {
	//Keep track of tick-tock on the clock
	static std::atomic<int64_t> timer_count_micros;
	static constexpr uint32_t numMicrosPerSecond = 100000;
	static bool enabledClock;

public:
	static bool isEnabled();
	static void SleepMicros(uint32_t micros);
	static void *UpdateTimerCounter(void* arg);
	pthread_t InitClock(uint32_t precision_micros);
};


#endif //TREELINE_TEST_TIMER_H
