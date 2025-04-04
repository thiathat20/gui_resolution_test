#ifndef STARTSTIMULVIEW_HPP
#define STARTSTIMULVIEW_HPP

#include <gui_generated/startstimul_screen/startStimulViewBase.hpp>
#include <gui/startstimul_screen/startStimulPresenter.hpp>

class startStimulView : public startStimulViewBase
{
public:
    startStimulView();
    virtual ~startStimulView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
protected:
};

#endif // STARTSTIMULVIEW_HPP
