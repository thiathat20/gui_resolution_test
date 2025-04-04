#ifndef SETSTUMULTIMEVIEW_HPP
#define SETSTUMULTIMEVIEW_HPP

#include <gui_generated/setstumultime_screen/setStumulTimeViewBase.hpp>
#include <gui/setstumultime_screen/setStumulTimePresenter.hpp>

class setStumulTimeView : public setStumulTimeViewBase
{
public:
    setStumulTimeView();
    virtual ~setStumulTimeView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
protected:
};

#endif // SETSTUMULTIMEVIEW_HPP
