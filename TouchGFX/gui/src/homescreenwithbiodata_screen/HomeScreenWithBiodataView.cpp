#include <gui/homescreenwithbiodata_screen/HomeScreenWithBiodataView.hpp>
#include "texts/TextKeysAndLanguages.hpp"
#include <touchgfx/Color.hpp> //rkdalfks
#include <touchgfx/hal/HAL.hpp> //rkdalfks
#include <touchgfx/Utils.hpp> //rkdalfks
#include <ctime> //rkdalfks
#include <touchgfx/transitions/WipeTransition.hpp>

#include "stdio.h"
#include <cstdlib>

#if !defined(gui_simulation)
extern RTC_TimeTypeDef sTime;
extern RTC_DateTypeDef sDate;
extern uint8_t timeUpdateFlag;
catM1Time nowTimeinfo;
#endif


HomeScreenWithBiodataView::HomeScreenWithBiodataView()
	: tickCounter(0), lastUpdateTime(0), digitalHours(0), digitalMinutes(0), digitalSeconds(0),
	  initialX(0), initialY(0)
{

}

void HomeScreenWithBiodataView::setupScreen()
{
    //Texts::setLanguage(KOREAN);
#if defined(gui_simulation)
    HomeScreenWithBiodataViewBase::setupScreen();

	time(&lastUpdateTime);
	struct tm* timeinfo = localtime(&lastUpdateTime);

	touchgfx::Unicode::snprintf(date_valueBuffer1, DATE_VALUEBUFFER1_SIZE, "%02d", timeinfo->tm_mon+1);
	touchgfx::Unicode::snprintf(date_valueBuffer2, DATE_VALUEBUFFER2_SIZE, "%02d", timeinfo->tm_mday);
	date_value.invalidate();

	Unicode::snprintf(year_valueBuffer, YEAR_VALUE_SIZE, "%04d", timeinfo->tm_year+1900);
	year_value.invalidate();

	digitalClock.setTime24Hour(timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);
	digitalClock.invalidate();
#else
	////////////// jh /////////////////
	HomeScreenWithBiodataViewBase::setupScreen();

	touchgfx::Unicode::snprintf(date_valueBuffer1, DATE_VALUEBUFFER1_SIZE, "%02d", sDate.Month);
	touchgfx::Unicode::snprintf(date_valueBuffer2, DATE_VALUEBUFFER2_SIZE, "%02d", sDate.Date);
	date_value.invalidate();

	Unicode::snprintf(year_valueBuffer, YEAR_VALUE_SIZE, "%04d", sDate.Year+2000);
	year_value.invalidate();

	digitalClock.setTime24Hour(sTime.Hours, sTime.Minutes, sTime.Seconds);
	digitalClock.invalidate();

	touchgfx::Unicode::snprintf(home_heartrate_valueBuffer, HOME_HEARTRATE_VALUE_SIZE, "%02u", ehg.ssHr);
	home_heartrate_value.invalidate();
	touchgfx::Unicode::snprintf(home_spo2_valueBuffer, HOME_SPO2_VALUE_SIZE, "%02u", ehg.ssSpo2);
	home_spo2_value.invalidate();
	touchgfx::Unicode::snprintf(home_steps_valueBuffer, HOME_STEPS_VALUE_SIZE, "%u", ehg.ssWalk);
	home_steps_value.invalidate();
#endif
}

void HomeScreenWithBiodataView::tearDownScreen()
{
    HomeScreenWithBiodataViewBase::tearDownScreen();
}

void HomeScreenWithBiodataView::handleTickEvent()
{
#if defined(gui_simulation)
	tickCounter++;

	if (tickCounter % 60 == 0) // 1�ʸ��� ������Ʈ
	{
		time_t currentTime;
		time(&currentTime);

		double secondsPassed = difftime(currentTime, lastUpdateTime);

		if (secondsPassed >= 1)
		{
			struct tm* timeinfo = localtime(&currentTime);

			digitalClock.setTime24Hour(timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);
			digitalClock.invalidate();

			lastUpdateTime = currentTime; // ������Ʈ�� �ð� ����
		}
	}
#else
	tickCounter++; // 1tick = about 17.72us

	if (tickCounter % (56433) == 0) // 1s = about 56433.4
	{
		time_t currentTime;
		time(&currentTime);

//		double secondsPassed = difftime(currentTime, lastUpdateTime);
//
//		if (secondsPassed >= 1)
//		{
//			struct tm* timeinfo = localtime(&currentTime);
//
//			digitalClock.setTime24Hour(timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);
//			digitalClock.invalidate();
//
//			lastUpdateTime = currentTime; // ������Ʈ�� �ð� ����
//		}

		////////////////// jh ///////////////////
		if(getTimeUpdatFlag){
			setTimeUpdatFlag(0);
			nowTimeinfo = getCatM1Time();
			sDate.Year = (uint8_t)nowTimeinfo.year;
			sDate.Month = (uint8_t)nowTimeinfo.month;
			sDate.Date = (uint8_t)nowTimeinfo.day;
			sTime.Hours = (uint8_t)nowTimeinfo.hour;
			sTime.Minutes = (uint8_t)nowTimeinfo.min;
			sTime.Seconds = (uint8_t)nowTimeinfo.sec;

			HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BIN);
			HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BIN);
		}
		HAL_RTC_GetTime(&hrtc, &sTime, RTC_FORMAT_BIN);
		HAL_RTC_GetDate(&hrtc, &sDate, RTC_FORMAT_BIN);

		//PRINT_INFO("Current Time: %02u:%02u:%02u\n", sTime.Hours, sTime.Minutes, sTime.Seconds);
		//PRINT_INFO("Current Date: %04u-%02u-%02u\n", sDate.Year + 2000, sDate.Month, sDate.Date);

		touchgfx::Unicode::snprintf(date_valueBuffer1, DATE_VALUEBUFFER1_SIZE, "%02d", sDate.Month);
		touchgfx::Unicode::snprintf(date_valueBuffer2, DATE_VALUEBUFFER2_SIZE, "%02d", sDate.Date);
		date_value.invalidate();

		Unicode::snprintf(year_valueBuffer, YEAR_VALUE_SIZE, "%04d", sDate.Year+2000);
		year_value.invalidate();

		digitalClock.setTime24Hour(sTime.Hours, sTime.Minutes, sTime.Seconds);
		digitalClock.invalidate();

		if(!ehg.canDisplayPPG) return;

		ehg.canDisplayPPG = 0;

		touchgfx::Unicode::snprintf(home_heartrate_valueBuffer, HOME_HEARTRATE_VALUE_SIZE, "%02u", ehg.ssHr);
		home_heartrate_value.invalidate();
		touchgfx::Unicode::snprintf(home_spo2_valueBuffer, HOME_SPO2_VALUE_SIZE, "%02u", ehg.ssSpo2);
		home_spo2_value.invalidate();
		touchgfx::Unicode::snprintf(home_steps_valueBuffer, HOME_STEPS_VALUE_SIZE, "%u", ehg.ssWalk);
		home_steps_value.invalidate();

//		touchgfx::Unicode::snprintf(heartrate_valueBuffer, HEARTRATE_VALUE_SIZE, "%02u", ehg.ssHr);
//		heartrate_value.invalidate();
//		touchgfx::Unicode::snprintf(spo2_valueBuffer, SPO2_VALUE_SIZE, "%02u", ehg.ssSpo2);
//		spo2_value.invalidate();
//		touchgfx::Unicode::snprintf(step_valueBuffer, STEP_VALUE_SIZE, "%u", ehg.ssWalk);
//		step_value.invalidate();
	}

	if (tickCounter % (56433/60) == 0) // 1s = about 56433.4
	{
		if(gesture == SlideDown){
			gesture = None;
			presenter->notifySwipeDown();
		}
		else if(gesture == SlideLeft){
			gesture = None;
			presenter->notifySwipeLeft();
		}
		else if(gesture == SlideRight){
			gesture = None;
			printf("slide right in HomeScreen \r\n");
			presenter->notifySwipeRight();
		}
	}
#endif
}

void HomeScreenWithBiodataView::handleSwipeDown()
{
	application().gotoswipedownfromHomeScreenCoverTransitionNorth();
}

void HomeScreenWithBiodataView::handleSwipeLeft()
{
	application().gotoStepsScreenScreenWipeTransitionEast();
}

void HomeScreenWithBiodataView::handleSwipeRight()
{
	//application().gotoSpo2ScreenScreenWipeTransitionWest();
	application().gotosetStumulTimeScreenWipeTransitionWest();
}

#if defined(gui_simulation)
void HomeScreenWithBiodataView::handleGestureEvent(const GestureEvent& evt) //rkdalfks
{
	int deltaX = 0, deltaY = 0;
	const int swipeThreshold = 20;
    if (evt.getType() == GestureEvent::SWIPE_VERTICAL)
    {
        deltaY = evt.getVelocity();
    }
    if (evt.getType() == GestureEvent::SWIPE_HORIZONTAL)
    {
    	deltaX = evt.getVelocity();
    }

    if (evt.getType() == GestureEvent::SWIPE_VERTICAL && abs(deltaY)>abs(deltaX))
    {
    	if(abs(deltaY) > swipeThreshold)
    	{
			if (deltaY > -20)
			{
				presenter->notifySwipeDown();
			}
    	}
    }
    else if (evt.getType() == GestureEvent::SWIPE_HORIZONTAL && abs(deltaY)<abs(deltaX))
    {
    	if(abs(deltaX) > swipeThreshold)
		{
			if (deltaX < 0)
			{
				presenter->notifySwipeLeft();
			}
			if (deltaX > 0)
			{
				presenter->notifySwipeRight();
			}
		}
    }

    HomeScreenWithBiodataViewBase::handleGestureEvent(evt);
}
#endif
