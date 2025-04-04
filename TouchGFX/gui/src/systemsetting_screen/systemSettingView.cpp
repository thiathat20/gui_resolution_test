#include <gui/systemsetting_screen/systemSettingView.hpp>
#include <touchgfx/Color.hpp>
#include <touchgfx/hal/HAL.hpp>
#include <touchgfx/Utils.hpp>

#if !defined(gui_simulation)
#include "bl6133.h"
#endif

systemSettingView::systemSettingView()
	: initialX(0), initialY(0)
{

}

void systemSettingView::setupScreen()
{
    systemSettingViewBase::setupScreen();
}

void systemSettingView::tearDownScreen()
{
    systemSettingViewBase::tearDownScreen();
}


void systemSettingView::handleSwipeRight() //rkdalfks
{
    // ȭ�� ��ȯ �ڵ�
    application().gotoSettingScreenScreenWipeTransitionWest();
}
#if defined(gui_simulation)
void systemSettingView::handleGestureEvent(const GestureEvent& evt) //rkdalfks
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
    systemSettingViewBase::handleGestureEvent(evt);
}
#else
void systemSettingView::handleTickEvent(){
	if(gesture == SlideRight){
	    gesture = None;
		presenter->notifySwipeRight();
	}
}
#endif
