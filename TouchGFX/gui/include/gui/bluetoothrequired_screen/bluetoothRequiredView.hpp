#ifndef BLUETOOTHREQUIREDVIEW_HPP
#define BLUETOOTHREQUIREDVIEW_HPP

#include <gui_generated/bluetoothrequired_screen/bluetoothRequiredViewBase.hpp>
#include <gui/bluetoothrequired_screen/bluetoothRequiredPresenter.hpp>

class bluetoothRequiredView : public bluetoothRequiredViewBase
{
public:
    bluetoothRequiredView();
    virtual ~bluetoothRequiredView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
protected:
};

#endif // BLUETOOTHREQUIREDVIEW_HPP
