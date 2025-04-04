#include <gui/screensetting_screen/screenSettingView.hpp>
#include <touchgfx/Color.hpp>
#include <touchgfx/hal/HAL.hpp>
#include <touchgfx/Utils.hpp>

#if !defined(gui_simulation)
#include "bl6133.h"
#endif

screenSettingView::screenSettingView()
	: initialX(0), initialY(0) //rkdalfks
{

}

void screenSettingView::setupScreen()
{
    screenSettingViewBase::setupScreen();
}

void screenSettingView::tearDownScreen()
{
    screenSettingViewBase::tearDownScreen();
}

void screenSettingView::handleSwipeRight()
{
    // ȭ�� ��ȯ �ڵ�
    application().gotoSettingScreenScreenWipeTransitionWest();
}

#if defined(gui_simulation)
void screenSettingView::handleGestureEvent(const GestureEvent& evt)
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
    screenSettingViewBase::handleGestureEvent(evt);
}
#else
void screenSettingView::handleTickEvent(){
	if(gesture == SlideRight){
	    gesture = None;
		presenter->notifySwipeRight();
	}
}
#endif
