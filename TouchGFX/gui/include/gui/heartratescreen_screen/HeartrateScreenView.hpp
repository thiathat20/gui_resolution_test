#ifndef HEARTRATESCREENVIEW_HPP
#define HEARTRATESCREENVIEW_HPP

#include <gui_generated/heartratescreen_screen/HeartrateScreenViewBase.hpp>
#include <gui/heartratescreen_screen/HeartrateScreenPresenter.hpp>

#if !defined(gui_simulation)
#include "bl6133.h"
#endif

class HeartrateScreenView : public HeartrateScreenViewBase
{
public:
    HeartrateScreenView();
    virtual ~HeartrateScreenView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    void handleSwipeRight(); //rkdalfks
    void handleSwipeLeft();
#if defined(gui_simulation)
    virtual void handleGestureEvent(const GestureEvent& evt); //rkdalfks
#else
    virtual void changeHRVal();
    virtual void handleTickEvent();
#endif

protected:

private: //rkdalfks
    int initialX; //rkdalfks
    int initialY; //rkdalfks
};

#endif // HEARTRATESCREENVIEW_HPP
