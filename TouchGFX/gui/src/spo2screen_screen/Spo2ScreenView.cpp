#include <gui/spo2screen_screen/Spo2ScreenView.hpp>
#include <touchgfx/Color.hpp> //rkdalfks
#include <touchgfx/hal/HAL.hpp> //rkdalfks
#include <touchgfx/Utils.hpp> //rkdalfks


Spo2ScreenView::Spo2ScreenView()
    : initialX(0), initialY(0) //rkdalfks
{
}

void Spo2ScreenView::setupScreen()
{
    Spo2ScreenViewBase::setupScreen();

	uint16_t ssSpo2 = 0;

#if !defined(gui_simulation)
	ssSpo2 = ehg.ssSpo2;
#endif
	touchgfx::Unicode::snprintf(spo2_valueBuffer, SPO2_VALUE_SIZE, "%02u", ssSpo2);
	spo2_value.invalidate();
}

void Spo2ScreenView::tearDownScreen()
{
    Spo2ScreenViewBase::tearDownScreen();
}


void Spo2ScreenView::handleSwipeRight() //rkdalfks
{
    // ȭ�� ��ȯ �ڵ�
    application().gotoHeartrateScreenScreenWipeTransitionWest();
}

void Spo2ScreenView::handleSwipeLeft() //rkdalfks
{
    // ȭ�� ��ȯ �ڵ�
    application().gotoHomeScreenWithBiodataScreenWipeTransitionEast();
}

#if defined(gui_simulation)
void Spo2ScreenView::handleGestureEvent(const GestureEvent& evt) //rkdalfks
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
			//if(deltaX < 0)
			//{
			//	presenter->notifySwipeLeft();
			//}
		}
	}
    Spo2ScreenViewBase::handleGestureEvent(evt);
}
#else
void Spo2ScreenView::changeSpo2Val(){
	touchgfx::Unicode::snprintf(spo2_valueBuffer, SPO2_VALUE_SIZE, "%02u", ehg.ssSpo2);
	spo2_value.invalidate();
}

uint32_t frameCountInteraction5Interval_local = 0;
void Spo2ScreenView::handleTickEvent(){

	frameCountInteraction5Interval_local++;
	if(frameCountInteraction5Interval_local == 60)
	{
		//Interaction5
		//When every N tick call changeSpo2Val on Spo2Screen
		//Call changeSpo2Val
		changeSpo2Val();
		frameCountInteraction5Interval_local = 0;
	}
	if(frameCountInteraction5Interval_local % 10 == 0)
	{
		if(gesture == SlideRight){
		    gesture = None;
		    printf("slide right in SpO2Screen \r\n");
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
