#ifndef SCREENSETTINGVIEW_HPP
#define SCREENSETTINGVIEW_HPP

#include <gui_generated/screensetting_screen/screenSettingViewBase.hpp>
#include <gui/screensetting_screen/screenSettingPresenter.hpp>

class screenSettingView : public screenSettingViewBase
{
public:
    screenSettingView();
    virtual ~screenSettingView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    void handleSwipeRight();
#if defined(gui_simulation)
    virtual void handleGestureEvent(const GestureEvent& evt); //rkdalfks
#else
    virtual void handleTickEvent();
#endif

protected:

private: //rkdalfks
    int initialX;
    int initialY;
};

#endif // SCREENSETTINGVIEW_HPP
