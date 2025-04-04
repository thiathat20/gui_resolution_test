#ifndef SETSTIMULSTRENGTHVIEW_HPP
#define SETSTIMULSTRENGTHVIEW_HPP

#include <gui_generated/setstimulstrength_screen/setStimulStrengthViewBase.hpp>
#include <gui/setstimulstrength_screen/setStimulStrengthPresenter.hpp>

class setStimulStrengthView : public setStimulStrengthViewBase
{
public:
    setStimulStrengthView();
    virtual ~setStimulStrengthView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
protected:
};

#endif // SETSTIMULSTRENGTHVIEW_HPP
