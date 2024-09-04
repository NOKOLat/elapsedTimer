/*
 * TIMStopWatch.h
 *
 *  Created on: Oct 17, 2020
 *      Author: conat
 */

#ifndef SRC_TIMSTOPWATCH_H_
#define SRC_TIMSTOPWATCH_H_

#include "main.h"
#include <cmath>

class ElapsedTimer {
public:
	ElapsedTimer(TIM_HandleTypeDef *htim=nullptr, uint32_t frequence = 1000000)
	:htim(htim),
	 frequence(frequence)
	{
		befCount = 0;
		count = 0;
		isStart = false;
	}

	/*
	 * Start or restart the timer.
	 * This function does not discard the previous number of millisecond elapsed
	 * Please use reset() before start() to make sure that the initial number of millisecond elapsed is 0
	 */
	void start();

	/*
	 * Stop the timer.
	 */
	void stop();

	/*
	 * Stop the timer and discard the number of  millisecond elapsed.
	 */
	void reset();

	/*
	 * Return the number of millisecond elapsed since previous start().
	 */
	float getTimeMS();

	uint64_t getCount();

	/*
	 * This function dose not have return value.
	 * Update internally the number of millisecond elapsed since previous start()
	 */
	void update();

	/*
	 * Test if the configurations are correct.
	 * Return true when the configurations are correct.
	 * Return false when the configurations are incorrect.
	 */
	bool selfTest();

private:
	TIM_HandleTypeDef *htim;
	const uint64_t frequence;
	uint64_t count;
	uint64_t befCount;
	bool isStart;
};

#endif /* SRC_TIMSTOPWATCH_H_ */
