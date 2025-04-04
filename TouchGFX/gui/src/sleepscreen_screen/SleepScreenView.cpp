#include <gui/sleepscreen_screen/SleepScreenView.hpp>
#include <touchgfx/Color.hpp> //rkdalfks
#include <touchgfx/hal/HAL.hpp> //rkdalfks
#include <touchgfx/Utils.hpp> //rkdalfks
#if !defined(gui_simulation)
#include "bl6133.h"
#endif

SleepScreenView::SleepScreenView()
    : initialX(0), initialY(0) //rkdalfks
{

}

void SleepScreenView::setupScreen()
{
    SleepScreenViewBase::setupScreen();
}

void SleepScreenView::tearDownScreen()
{
    SleepScreenViewBase::tearDownScreen();
}

void SleepScreenView::handleSwipeRight() //rkdalfks
{
    // ȭ�� ��ȯ �ڵ�
    application().gotoSpo2ScreenScreenSlideTransitionWest();
}

#if defined(gui_simulation)
void SleepScreenView::handleGestureEvent(const GestureEvent& evt) //rkdalfks
{
    if (evt.getType() == GestureEvent::SWIPE_HORIZONTAL)
    {
    	int deltaX = evt.getVelocity();
        //int deltaY = evt.getVelocityY();

        //if(abs(deltaX)>abs(deltaY))
        //{
			if (deltaX > 0)
			{
				presenter->notifySwipeRight();
			}
        //}
    }
    SleepScreenViewBase::handleGestureEvent(evt);
}
#else
void SleepScreenView::handleTickEvent(){
	if(gesture == SlideRight){
	    gesture = None;
//		presenter->notifySwipeRight();
	}
}
#endif
