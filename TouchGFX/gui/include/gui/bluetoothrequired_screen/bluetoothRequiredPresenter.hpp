#ifndef BLUETOOTHREQUIREDPRESENTER_HPP
#define BLUETOOTHREQUIREDPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class bluetoothRequiredView;

class bluetoothRequiredPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    bluetoothRequiredPresenter(bluetoothRequiredView& v);

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

    virtual ~bluetoothRequiredPresenter() {}

private:
    bluetoothRequiredPresenter();

    bluetoothRequiredView& view;
};

#endif // BLUETOOTHREQUIREDPRESENTER_HPP
