#ifndef INFORMATIONSETTINGVIEW_HPP
#define INFORMATIONSETTINGVIEW_HPP

#include <gui_generated/informationsetting_screen/informationSettingViewBase.hpp>
#include <gui/informationsetting_screen/informationSettingPresenter.hpp>

class informationSettingView : public informationSettingViewBase
{
public:
    informationSettingView();
    virtual ~informationSettingView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    void handleSwipeRight();
#if defined(gui_simulation)
    virtual void handleGestureEvent(const GestureEvent& evt);
#else
    virtual void handleTickEvent();
#endif
protected:

private:
    int initialX;
    int initialY;
};

#endif // INFORMATIONSETTINGVIEW_HPP
