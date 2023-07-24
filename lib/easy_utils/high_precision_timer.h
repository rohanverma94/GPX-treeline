//
// Created by rohandev on 7/23/23.
//

#ifndef TREELINE_TEST_HIGH_PRECISION_TIMER_H
#define TREELINE_TEST_HIGH_PRECISION_TIMER_H

#include <cstdint>

#include <atomic>
#include <pthread.h>

class high_precision_timer {

	static std::atomic<int64_t> timer_count_micros;
	static constexpr uint64_t kPrecisionMicros = 50;
	static constexpr uint32_t kNumMicrosPerSecond = 100000;

	static void *UpdateTimerCounter(void *arg);

	pthread_t InitCacheClock();
};


#endif //TREELINE_TEST_HIGH_PRECISION_TIMER_H
