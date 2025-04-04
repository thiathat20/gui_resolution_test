#include <gui/stepsscreen_screen/StepsScreenView.hpp>
#include <touchgfx/Color.hpp> //rkdalfks
#include <touchgfx/hal/HAL.hpp> //rkdalfks
#include <touchgfx/Utils.hpp> //rkdalfks

#if !defined(gui_simulation)
#include "bl6133.h"
#endif

StepsScreenView::StepsScreenView() //rkdalfks
	: initialX(0), initialY(0)
{

}

void StepsScreenView::setupScreen()
{
    StepsScreenViewBase::setupScreen();

    uint32_t ssWalk = 0;
#if !defined(gui_simulation)
    ssWalk = ehg.ssWalk;
#endif
	touchgfx::Unicode::snprintf(steps_valueBuffer, STEPS_VALUE_SIZE, "%02u", ssWalk);
	steps_value.invalidate();
}

void StepsScreenView::tearDownScreen()
{
    StepsScreenViewBase::tearDownScreen();
}


void StepsScreenView::handleSwipeRight() //rkdalfks
{
	application().gotoHomeScreenWithBiodataScreenWipeTransitionWest();
}

void StepsScreenView::handleSwipeLeft() //rkdalfks
{
	application().gotoHeartrateScreenScreenWipeTransitionEast();
}

#if defined(gui_simulation)
void StepsScreenView::handleGestureEvent(const GestureEvent& evt) //rkdalfks
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
	StepsScreenViewBase::handleGestureEvent(evt);
}
#else
void StepsScreenView::changeStepVal(){
	touchgfx::Unicode::snprintf(steps_valueBuffer, STEPS_VALUE_SIZE, "%02u", ehg.ssWalk);
	steps_value.invalidate();
}

uint32_t frameCountInteraction3Interval_local = 0;
void StepsScreenView::handleTickEvent(){

	frameCountInteraction3Interval_local++;
	if(frameCountInteraction3Interval_local == 60)
	{
		//Interaction3
		//When every N tick call changeStepVal on StepsScreen
		//Call changeStepVal
		changeStepVal();
		frameCountInteraction3Interval_local = 0;
	}
	if(frameCountInteraction3Interval_local % 10 == 0)
	{
		if(gesture == SlideRight){
		    gesture = None;
		    printf("slide right in StepsScreen \r\n");
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
