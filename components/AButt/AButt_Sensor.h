#pragma once

#include "esphome/core/component.h"
#include "esphome/core/hal.h"
#include "esphome/components/sensor/sensor.h"

#define INODE_SET_METHOD(type, name, default) \
  type name##_{default}; \
  void set_##name(type name) { name##_ = name; }

namespace esphome {
namespace aButt_sensor {

class AButtSensor : public sensor::Sensor, public Component {
public:
  void setup() override;
  void loop() override;
  void dump_config() override;
  float get_setup_priority() const override { return esphome::setup_priority::HARDWARE; }

  INODE_SET_METHOD(GPIOPin*, pin, nullptr);
  INODE_SET_METHOD(unsigned int, debounce, 50);

  INODE_SET_METHOD(unsigned int, clickDelay, 500); // time before a click is registered as a new sequense
  INODE_SET_METHOD(unsigned int, holdDelay, 700); // time before a click becomes a hold
  INODE_SET_METHOD(unsigned short, maxClicks, 5); // maximum number of clicks in a sequence
    
protected:
  bool 
    _isPressed = false, //is btn pressed. This INCLUDES the debounce compensation.
   _isHeld = false,     //is the btn beeing hold?
   _wasPressed = false, //was btn pressed. This INCLUDES the debounce compensation.
   _lastState = false;  //state of button in previous update 

  short clickCount = 0; //counting the number of double clicks

  unsigned long 
    _lastDebounceTime = 0, //start last btn state change
    _lastPressTime = 0,    //start of the last btn press, including de-bounce
    _lastClickTime = 0,    //start of the last btn release, including de-bounce

    resetStateDelay_ = 500, 
    timerStart_ = 0;

  void finishClick();

  void startHold();
  void endHold();
};

} //namespace empty_sensor
} //namespace esphome
