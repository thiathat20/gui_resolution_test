#include <gui/heartratescreen_screen/HeartrateScreenView.hpp>
#include <touchgfx/Color.hpp> //rkdalfks
#include <touchgfx/hal/HAL.hpp> //rkdalfks
#include <touchgfx/Utils.hpp> //rkdalfks

#if !defined(gui_simulation)
#include "bl6133.h"
#endif

HeartrateScreenView::HeartrateScreenView()
	: initialX(0), initialY(0) //rkdalfks
{

}

void HeartrateScreenView::setupScreen()
{
    HeartrateScreenViewBase::setupScreen();

	uint16_t ssHr = 0;
#if !defined(gui_simulation)
	ssHr = ehg.ssHr;
#endif
	touchgfx::Unicode::snprintf(heartrate_valueBuffer, HEARTRATE_VALUE_SIZE, "%02u", ssHr);
	heartrate_value.invalidate();
}

void HeartrateScreenView::tearDownScreen()
{
    HeartrateScreenViewBase::tearDownScreen();
}
void HeartrateScreenView::handleSwipeRight() //rkdalfks
{
	application().gotoStepsScreenScreenWipeTransitionWest();
}

void HeartrateScreenView::handleSwipeLeft() //rkdalfks
{
	application().gotoSpo2ScreenScreenWipeTransitionEast();
}

#if defined(gui_simulation)
void HeartrateScreenView::handleGestureEvent(const GestureEvent& evt) //rkdalfks
{
	const int swipeThreshold = 20;
	if (evt.getType()==GestureEvent::SWIPE_HORIZONTAL)
	{
    	int deltaX = evt.getVelocity();

    	if(abs(deltaX) > swipeThreshold)
    	{
    		if(deltaX > 0)
			{
				presenter->notifySwipeRight();
			}
    		if(deltaX < 0)
			{
				presenter->notifySwipeLeft();
			}
    	}
	}
	HeartrateScreenViewBase::handleGestureEvent(evt);
}
#else
void HeartrateScreenView::changeHRVal(){
	touchgfx::Unicode::snprintf(heartrate_valueBuffer, HEARTRATE_VALUE_SIZE, "%02u", ehg.ssHr);
	heartrate_value.invalidate();
}

uint32_t frameCountInteraction4Interval_local=0;
void HeartrateScreenView::handleTickEvent(){

	frameCountInteraction4Interval_local++;
	if(frameCountInteraction4Interval_local == 60)
	{
		//Interaction4
		//When every N tick call changeHRVal on HeartrateScreen
		//Call changeHRVal
		changeHRVal();
		frameCountInteraction4Interval_local = 0;
	}
	if(frameCountInteraction4Interval_local % 10 == 0)
	{
		if(gesture == SlideRight){
		    gesture = None;
		    printf("slide right in HeartateScreen \r\n");
			presenter->notifySwipeRight();
		}
		else if(gesture == SlideLeft){
		    gesture = None;
			presenter->notifySwipeLeft();
		}
		else if(gesture == SlideDown){
		    gesture = None;
			application().gotoswipedownfromHomeScreenCoverTransitionNorth();
		}
		else if(gesture == LongPress){
		    gesture = None;
			application().gotoHomeScreenWithBiodataScreenWipeTransitionWest();
		}
	}
}
#endif
