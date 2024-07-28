/*
 * TIMStopWatch.cpp
 *
 *  Created on: Oct 17, 2020
 *      Author: conat
 */

#include "./elapsedTimer.h"

void ElapsedTimer::start(){
	update();
	HAL_TIM_Base_Start(htim);
	isStart = true;
}

void ElapsedTimer::stop(){
	isStart = false;
	HAL_TIM_Base_Stop(htim);
}

void ElapsedTimer::reset(){
	stop();
	count = 0;
	befCount = 0;
	__HAL_TIM_SET_COUNTER(htim, 0);
	__HAL_TIM_CLEAR_FLAG(htim, TIM_FLAG_UPDATE);
}

void ElapsedTimer::update(){
	uint32_t cnt = __HAL_TIM_GET_COUNTER(htim);

	if (__HAL_TIM_GET_FLAG(htim, TIM_FLAG_UPDATE)) {//over_flow
		count += cnt - (befCount - __HAL_TIM_GET_AUTORELOAD(htim));
		__HAL_TIM_CLEAR_FLAG(htim, TIM_FLAG_UPDATE);
	} else {
		count += cnt - befCount;
	}

	befCount = cnt;
}

float ElapsedTimer::getTimeMS(){
	update();
	return count / (float)frequence * 1000.0f;
}

bool ElapsedTimer::selfTest(){
	const int testDuration = 1000;
	reset();
	start();
	HAL_Delay(testDuration);

	bool res = false;

	if(std::pow(getTimeMS() - testDuration,2)<testDuration*0.001){
		//acceptable error limit is 0.1% of testDuration
		return true;
	}

	reset();

	return res;

}
