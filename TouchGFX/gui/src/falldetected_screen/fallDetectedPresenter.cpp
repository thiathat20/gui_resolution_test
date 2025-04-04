#include <gui/falldetected_screen/fallDetectedView.hpp>
#include <gui/falldetected_screen/fallDetectedPresenter.hpp>

fallDetectedPresenter::fallDetectedPresenter(fallDetectedView& v)
    : view(v)
{

}

void fallDetectedPresenter::activate()
{

}

void fallDetectedPresenter::deactivate()
{

}

void fallDetectedPresenter::fall_detect_screen_display()
{
  view.changeToFallDetected();
}
