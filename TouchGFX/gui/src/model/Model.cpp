#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>

#include <gui/common/FrontendApplication.hpp>

#ifndef SIMULATOR
#include "main.h"

extern "C"{
  message_t msgData_r;
}
#endif

Model::Model()
	: modelListener(0),
	  toggleButton1State(true), //test
	  toggleButton2State(true),
	  slider1Value(50)
{
}

void Model::tick()
{
//	tickCounter++;
//	if(tickCounter % 60 == 0)
//	{
//		if(modelListener){
//			modelListener->updateClock();
//		}
//	}
#ifndef SIMULATOR
  //modelListener->notifyTemperatureChanged(cwData.temperature);

  if (osMessageQueueGetCount(guiQueueHandle) > 0)
  {
    if (osMessageQueueGet(guiQueueHandle, &msgData_r, 0, 0) == osOK)
    {
      printf("Recv GUI MSG : %d\r\n", (msgData_r.msgType));
      switch(msgData_r.msgType) {
        case BLACK_SCREEN:
          static_cast<FrontendApplication*>(touchgfx::Application::getInstance())->gotoinitBlackScreenScreenNoTransition();
          break;
        case CHARGE_SCREEN:
          static_cast<FrontendApplication*>(touchgfx::Application::getInstance())->gotocharging_screenScreenNoTransition();
          break;
        case UNCHARGE_SCREEN:
          static_cast<FrontendApplication*>(touchgfx::Application::getInstance())->gotounCharging_screenScreenNoTransition();
          break;
        case SOS_ALERT:
          static_cast<FrontendApplication*>(touchgfx::Application::getInstance())->gotosos_alertScreenNoTransition();
          break;
        case HOME_SCREEN:
          static_cast<FrontendApplication*>(touchgfx::Application::getInstance())->gotoHomeScreenWithBiodataScreenNoTransition();
          break;
        case FALL_DETECTION:
          static_cast<FrontendApplication*>(touchgfx::Application::getInstance())->gotofallDetectedScreenNoTransition();
          break;
      }
    }
  }
#endif

}

void Model::setToggleButton1State(bool state)
{
    if (toggleButton1State != state)
    {
        toggleButton1State = state;
        if (toggleButton1StateChangedCallback.isValid())
        {
            toggleButton1StateChangedCallback.execute(toggleButton1State);
        }
    }
}

void Model::setToggleButton2State(bool state)
{
    if (toggleButton2State != state)
    {
        toggleButton2State = state;
        if (toggleButton2StateChangedCallback.isValid())
        {
            toggleButton2StateChangedCallback.execute(toggleButton2State);
        }
    }
}

bool Model::getToggleButton1State() const
{
    return toggleButton1State;
}

bool Model::getToggleButton2State() const
{
    return toggleButton2State;
}

void Model::setSlider1Value(int value) //test
{
	slider1Value = value;
}

int Model::getSlider1Value() const //test
{
	return slider1Value;
}
