#ifndef SETSTIMULSTRENGTHPRESENTER_HPP
#define SETSTIMULSTRENGTHPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class setStimulStrengthView;

class setStimulStrengthPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    setStimulStrengthPresenter(setStimulStrengthView& v);

    /**
     * The activate function is called automatically when this screen is "switched in"
     * (ie. made active). Initialization logic can be placed here.
     */
    virtual void activate();

    /**
     * The deactivate function is called automatically when this screen is "switched out"
     * (ie. made inactive). Teardown functionality can be placed here.
     */
    virtual void deactivate();

    virtual ~setStimulStrengthPresenter() {}

private:
    setStimulStrengthPresenter();

    setStimulStrengthView& view;
};

#endif // SETSTIMULSTRENGTHPRESENTER_HPP
