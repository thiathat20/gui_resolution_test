#include <gui/flashlight_screen_screen/flashlight_screenView.hpp>

flashlight_screenView::flashlight_screenView()
{

}

void flashlight_screenView::setupScreen()
{
    flashlight_screenViewBase::setupScreen();
}

void flashlight_screenView::tearDownScreen()
{
    flashlight_screenViewBase::tearDownScreen();
}

#if !defined(gui_simulation)
void flashlight_screenView::changeMaxBrightness(){
	ehg.before_bLevel = ehg.set_bLevel;
	ehg.set_bLevel = 16;
	ehg.flashlightOn = 1;
}

void flashlight_screenView::changeBeforeBrightness(){
	ehg.set_bLevel = ehg.before_bLevel;
	ehg.flashlightOn = 0;
}
#endif
