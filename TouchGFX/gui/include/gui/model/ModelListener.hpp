#ifndef MODELLISTENER_HPP
#define MODELLISTENER_HPP

#include <gui/model/Model.hpp>

class ModelListener
{
public:
    ModelListener() : model(0) {}
    
    virtual ~ModelListener() {}
    virtual void updateClock() {} //rkdalfks

    void bind(Model* m)
    {
        model = m;
    }

  virtual void black_screen_display(){}
  virtual void charge_screen_display(){}
  virtual void uncharge_screen_display(){}
  virtual void sos_alert_display(){}
  virtual void home_screen_display(){}
  virtual void fall_detect_screen_display(){}

protected:
    Model* model;
};

#endif // MODELLISTENER_HPP
