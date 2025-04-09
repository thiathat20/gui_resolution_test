/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : STM32TouchController.cpp
  ******************************************************************************
  * This file was created by TouchGFX Generator 4.23.2. This file is only
  * generated once! Delete this file from your project and re-generate code
  * using STM32CubeMX or change this file manually to update it.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* USER CODE BEGIN STM32TouchController */

#include <STM32TouchController.hpp>

#include "bl6133.h"

void STM32TouchController::init()
{
    /**
     * Initialize touch controller and driver
     *
     */
}

uint8_t touchData[6] = {0,};
GESTURE gesture = None;
GESTURE lastGesture = None;
int32_t before_x = 0;
int32_t before_y = 0;
uint8_t touchDetectFlag = 1;
int test_count = 0;
bool STM32TouchController::sampleTouch(int32_t& x, int32_t& y)
{
    /**
     * By default sampleTouch returns false,
     * return true if a touch has been detected, otherwise false.
     *
     * Coordinates are passed to the caller by reference by x and y.
     *
     * This function is called by the TouchGFX framework.
     * By default sampleTouch is called every tick, this can be adjusted by HAL::setTouchSampleRate(int8_t);
     *
     */
	if(!ehg.occurred_touchInterrupt) {
		test_count++;
		return false; // ????? ???????????? ??? ??????,.. ¦��??? ?????????
	}
//	HAL_Delay(25);
	touchDetectFlag = touchDetect(touchData);

	uint8_t err = readTouchData(touchData, sizeof(touchData));

	if(err) return false;


	gesture = static_cast<GESTURE>(touchData[0]);
//	HAL_Delay(14); // debouncing

	uint8_t normalTouch = 1;
	switch(gesture){
		case None: // Drag
			x = read_x(touchData);
			y = read_y(touchData);
			break;
		case SingleTap: // touch
			x = read_x(touchData);
			y = read_y(touchData);
			lastGesture = gesture;
			break;
		default: // slide
			lastGesture = gesture;
			normalTouch = 0;
	}

	// long(C) > D-tap(B) > slide(1~4) > S-tap(5) > non(0) : 우선순위 적용?


	test_count = 0;
	if(normalTouch == 1){
		return true;
	} else {
		return false;
	}


//	//////// touch state check (�հ��� ������ �Է� �ǵ���) /////////
//
//	if(!ehg.occurred_touchInterrupt) return false; // ????? ???????????? ??? ??????,.. ¦��??? ?????????
//
//	touchDetectFlag = touchDetect(touchData);
//
//	uint8_t err = readTouchData(touchData, sizeof(touchData));
//
//	if(err) return false;
//
//	now_touchState = touchData[1]; // 1: touch, 0: no touch
//
//	gesture = static_cast<GESTURE>(touchData[0]);
//	HAL_Delay(20); // debouncing
//
//	uint8_t normalTouch = 0;
//	switch(gesture){
//		case None:
//			x = read_x(touchData);
//			y = read_y(touchData);
//			normalTouch = 1;
//			break;
//		case SingleTap:
//			x = read_x(touchData);
//			y = read_y(touchData);
//			lastGesture = gesture;
//			normalTouch = 1;
//			break;
//		default: // slide interrupt
//			lastGesture = gesture;
//	}
//
//	if(normalTouch){
//		if(pre_touchState == 1 && now_touchState == 0){
//			pre_touchState = now_touchState;
//			return true;
//		} else {
//			pre_touchState = now_touchState;
//			return false;
//		}
//	} else {
//		pre_touchState = now_touchState;
//		return false;
//	}


}

/* USER CODE END STM32TouchController */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
