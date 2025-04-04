#include <gui/informationsetting_screen/informationSettingView.hpp>
#include <touchgfx/Color.hpp>
#include <touchgfx/hal/HAL.hpp>
#include <touchgfx/Utils.hpp>

#if !defined(gui_simulation)
#include "bl6133.h"
#endif

informationSettingView::informationSettingView()
	: initialX(0), initialY(0)
{

}

void informationSettingView::setupScreen()
{
    informationSettingViewBase::setupScreen();
}

void informationSettingView::tearDownScreen()
{
    informationSettingViewBase::tearDownScreen();
}

void informationSettingView::handleSwipeRight() //rkdalfks
{
    // ȭ�� ��ȯ �ڵ�
    application().gotoSettingScreenScreenWipeTransitionWest();
}

#if defined(gui_simulation)
void informationSettingView::handleGestureEvent(const GestureEvent& evt) //rkdalfks
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
    informationSettingViewBase::handleGestureEvent(evt);
}
#else
void informationSettingView::handleTickEvent(){
	if(gesture == SlideRight){
	    gesture = None;
		presenter->notifySwipeRight();
	}
}
#endif
