/*
 * TIMStopWatch.cpp
 *
 *  Created on: Oct 17, 2020
 *      Author: conat
 */

#include "TIMStopWatch.h"

void TIM_StopWatch::start(){
	update();
	HAL_TIM_Base_Start(htim);
	isStart = true;
}

void TIM_StopWatch::stop(){
	isStart = false;
	HAL_TIM_Base_Stop(htim);
}

void TIM_StopWatch::reset(){
	stop();
	count = 0;
	__HAL_TIM_SET_COUNTER(htim, 0);
	__HAL_TIM_CLEAR_FLAG(htim, TIM_FLAG_UPDATE);
}

void TIM_StopWatch::update(){
	uint32_t cnt = __HAL_TIM_GET_COUNTER(htim);

	if (__HAL_TIM_GET_FLAG(htim, TIM_FLAG_UPDATE)) {//over_flow
		count += cnt - (befCount - __HAL_TIM_GET_AUTORELOAD(htim));
		__HAL_TIM_CLEAR_FLAG(htim, TIM_FLAG_UPDATE);
	} else {
		count += cnt - befCount;
	}

	befCount = cnt;
}

float TIM_StopWatch::getTimeMS(){
	return count / (float)frequence * 1000.0f;
}
