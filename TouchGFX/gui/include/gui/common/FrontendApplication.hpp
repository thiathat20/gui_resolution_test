#ifndef FRONTENDAPPLICATION_HPP
#define FRONTENDAPPLICATION_HPP

//#define gui_simulation

#if !defined(gui_simulation)
#include "main.h"
#include "bl6133.h"
#include "nrf9160.h"
#include "rtc.h"
#endif

#include <gui_generated/common/FrontendApplicationBase.hpp>
#include <texts/TextKeysAndLanguages.hpp> //rkdalfks
#include <mvp/View.hpp> //rkdalfks
#include <mvp/Presenter.hpp> //rkdalfks
#include <touchgfx/hal/HAL.hpp> //rkdalfks
#include <touchgfx/Application.hpp> //rkdalfks

class FrontendHeap;

using namespace touchgfx;

class FrontendApplication : public FrontendApplicationBase
{
public:
    FrontendApplication(Model& m, FrontendHeap& heap);
    virtual ~FrontendApplication() { }

    virtual void handleTickEvent()
    {
        model.tick();
        FrontendApplicationBase::handleTickEvent();
    }
private:
};

#endif // FRONTENDAPPLICATION_HPP
