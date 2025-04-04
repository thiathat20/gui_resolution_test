#ifndef MODEL_HPP
#define MODEL_HPP

#include <stdint.h>

#include <touchgfx/Utils.hpp>
#include <touchgfx/Callback.hpp>

class ModelListener;

class Model
{
public:
    Model();

    void bind(ModelListener* listener)
    {
        modelListener = listener;
    }

    void tick();

    void setToggleButton1State(bool state);
    bool getToggleButton1State() const;
    void setToggleButton2State(bool state);
    bool getToggleButton2State() const;

    void setSlider1Value(int value); //test
    int getSlider1Value() const; //test

    touchgfx::GenericCallback<bool>& getToggleButton1StateChangedCallback() { return toggleButton1StateChangedCallback; }
    touchgfx::GenericCallback<bool>& getToggleButton2StateChangedCallback() { return toggleButton2StateChangedCallback; }

protected:
    ModelListener* modelListener;
    int tickCounter; //rkdalfks

private:
    bool toggleButton1State;
    bool toggleButton2State;

    int slider1Value; //test

    touchgfx::Callback<Model, bool> toggleButton1StateChangedCallback;
    touchgfx::Callback<Model, bool> toggleButton2StateChangedCallback;
};

#endif // MODEL_HPP
