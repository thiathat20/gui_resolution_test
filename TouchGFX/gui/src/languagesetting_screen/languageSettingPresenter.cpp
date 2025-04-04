#include <gui/languagesetting_screen/languageSettingView.hpp>
#include <gui/languagesetting_screen/languageSettingPresenter.hpp>

languageSettingPresenter::languageSettingPresenter(languageSettingView& v)
    : view(v)
{

}

void languageSettingPresenter::activate()
{

}

void languageSettingPresenter::deactivate()
{

}

void languageSettingPresenter::notifySwipeRight()
{
	view.handleSwipeRight();
}
