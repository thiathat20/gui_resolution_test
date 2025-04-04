#ifndef HOMESCREENWITHBIODATAPRESENTER_HPP
#define HOMESCREENWITHBIODATAPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class HomeScreenWithBiodataView;

class HomeScreenWithBiodataPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    HomeScreenWithBiodataPresenter(HomeScreenWithBiodataView& v);

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
    virtual void notifySwipeDown();
    virtual void notifySwipeLeft();
    virtual void notifySwipeRight();

    virtual ~HomeScreenWithBiodataPresenter() {};

private:
    HomeScreenWithBiodataPresenter();

    HomeScreenWithBiodataView& view;
};

#endif // HOMESCREENWITHBIODATAPRESENTER_HPP
