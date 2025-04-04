#ifndef SWIPEDOWNFROMHOMEPRESENTER_HPP
#define SWIPEDOWNFROMHOMEPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>
#include <touchgfx/Callback.hpp>

using namespace touchgfx;

class swipedownfromHomeView;

class swipedownfromHomePresenter : public touchgfx::Presenter, public ModelListener
{
public:
    swipedownfromHomePresenter(swipedownfromHomeView& v);

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
    virtual void notifySwipeUp();

    void updateToggleButton1State(bool state);
    bool getToggleButton1State() const;
    void onToggleButton1StateChanged(bool state);

    void updateToggleButton2State(bool state);
    bool getToggleButton2State() const;
    void onToggleButton2StateChanged(bool state);

    void updateSlider1Value(int value); //test
    int getSlider1Value() const;

    virtual ~swipedownfromHomePresenter() {};

private:
    swipedownfromHomePresenter();

    swipedownfromHomeView& view;
};

#endif // SWIPEDOWNFROMHOMEPRESENTER_HPP
