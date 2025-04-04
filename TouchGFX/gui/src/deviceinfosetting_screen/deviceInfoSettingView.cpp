#include <gui/deviceinfosetting_screen/deviceInfoSettingView.hpp>
#include <touchgfx/Color.hpp>
#include <touchgfx/hal/HAL.hpp>
#include <touchgfx/Utils.hpp>

#if !defined(gui_simulation)
#include "main.h"
#endif

deviceInfoSettingView::deviceInfoSettingView()
	: initialX(0), initialY(0)
{

}

void deviceInfoSettingView::setupScreen()
{
    deviceInfoSettingViewBase::setupScreen();

    char model[6] = "eHG4M";
    char version[7] = "v1.0.0";
    char serviceNumber_ascii[16+1] = {0,};
    uint32_t deviceID = 0;
#if !defined(gui_simulation)
    uint64_t serviceNumber = 0;
    deviceID = ehg.deviceID;
    extern cat_m1_at_cmd_rst_t cat_m1_at_cmd_rst;
    memcpy(serviceNumber_ascii, &cat_m1_at_cmd_rst.cnum[4], 16);
    serviceNumber = atoi(serviceNumber_ascii);
#endif

//    char strDeviceID[10];
//
//    sprintf(strDeviceID, "%d", deviceID);

	Unicode::snprintf(model_labelBuffer, MODEL_LABEL_SIZE, model);
	model_label.invalidate();
	Unicode::snprintf(version_labelBuffer, VERSION_LABEL_SIZE, version);
	version_label.invalidate();
	Unicode::snprintf(id_labelBuffer, ID_LABEL_SIZE, "0x%.8x", deviceID);
	id_label.invalidate();
	Unicode::snprintf(servicenumber_labelBuffer, SERVICENUMBER_LABEL_SIZE, serviceNumber_ascii);
	servicenumber_label.invalidate();
}

void deviceInfoSettingView::tearDownScreen()
{
    deviceInfoSettingViewBase::tearDownScreen();
}
#if defined(gui_simulation)
void deviceInfoSettingView::handleGestureEvent(const GestureEvent& evt)
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
    deviceInfoSettingViewBase::handleGestureEvent(evt);
}
#endif

void deviceInfoSettingView::handleSwipeRight()
{
    // ȭ�� ��ȯ �ڵ�
    application().gotoinformationSettingScreenWipeTransitionWest();
}

#if !defined(gui_simulation)
void deviceInfoSettingView::handleTickEvent(){
	if(gesture == SlideRight){
	    gesture = None;
		presenter->notifySwipeRight();
	}
}
#endif
