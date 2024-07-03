/*
 * TIMStopWatch.h
 *
 *  Created on: Oct 17, 2020
 *      Author: conat
 */

#ifndef SRC_TIMSTOPWATCH_H_
#define SRC_TIMSTOPWATCH_H_

#include "main.h"

class ElapsedTimer {
public:
	ElapsedTimer(TIM_HandleTypeDef *htim=nullptr, uint32_t frequence = 1000000)
	:htim(htim),
	 frequence(frequence)
	{
	}

	void start();
	void stop();
	void reset();
	float getTimeMS();
	void update();
	bool selfTest();

private:
	TIM_HandleTypeDef *htim;
	const uint32_t frequence;
	uint32_t count = 0;
	uint32_t befCount = 0;
	bool isStart = false;
};

#endif /* SRC_TIMSTOPWATCH_H_ */
