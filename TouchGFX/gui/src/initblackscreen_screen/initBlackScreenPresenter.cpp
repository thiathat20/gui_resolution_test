#include <gui/initblackscreen_screen/initBlackScreenView.hpp>
#include <gui/initblackscreen_screen/initBlackScreenPresenter.hpp>

initBlackScreenPresenter::initBlackScreenPresenter(initBlackScreenView& v)
    : view(v)
{

}

void initBlackScreenPresenter::activate()
{

}

void initBlackScreenPresenter::deactivate()
{

}

void initBlackScreenPresenter::black_screen_display()
{
  view.changeToInitBlackScreen();
}

