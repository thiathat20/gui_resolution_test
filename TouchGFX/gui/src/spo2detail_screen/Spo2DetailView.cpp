#include <gui/spo2detail_screen/Spo2DetailView.hpp>
#include <touchgfx/Color.hpp> //rkdalfks
#include <touchgfx/hal/HAL.hpp> //rkdalfks
#include <touchgfx/Utils.hpp> //rkdalfks

#if !defined(gui_simulation)
#include "bl6133.h"
#endif

Spo2DetailView::Spo2DetailView()
{

}

void Spo2DetailView::setupScreen()
{
    Spo2DetailViewBase::setupScreen();
}

void Spo2DetailView::tearDownScreen()
{
    Spo2DetailViewBase::tearDownScreen();
}

void Spo2DetailView::handleSwipeRight() //rkdalfks
{
	application().gotoHomeScreenWithBiodataScreenWipeTransitionWest();
}

#if defined(gui_simulation)
void Spo2DetailView::handleGestureEvent(const GestureEvent& evt) //rkdalfks
{
	if (evt.getType()==GestureEvent::SWIPE_HORIZONTAL)
	{
    	int deltaX = evt.getVelocity();
        //int deltaY = evt.getVelocityY();

        //if(abs(deltaX)>abs(deltaY))
        //{
			if(deltaX>0)
			{
				presenter->notifySwipeRight();
			}
        //}
	}
	Spo2DetailViewBase::handleGestureEvent(evt);
}
#else
#define TICK_UPDATESPO2_INTERVAL 60
uint32_t frameCountUpdateSpo2Interval_local = 0;
void Spo2DetailView::handleTickEvent(){
	if(gesture == SlideRight){
	    gesture = None;
		presenter->notifySwipeRight();
	}

	frameCountUpdateSpo2Interval_local++;
	if(frameCountUpdateSpo2Interval_local == TICK_UPDATESPO2_INTERVAL)
	{
		if(!ehg.canDisplayPPG) return;

		ehg.canDisplayPPG = 0;

		touchgfx::Unicode::snprintf(spo2_valueBuffer, SPO2_VALUE_SIZE, "%02u", ehg.ssSpo2);
		spo2_value.invalidate();
		frameCountUpdateSpo2Interval_local = 0;
	}
}
#endif
