#pragma once

#include "esphome/core/component.h"
#include "esphome/components/sensor/sensor.h"

class AButt;

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

    INODE_SET_METHOD(int, pin, 0);
    INODE_SET_METHOD(bool, inverted, false);
    INODE_SET_METHOD(bool, isDigital, true);
    INODE_SET_METHOD(unsigned int, debounce, 50);

    INODE_SET_METHOD(unsigned int, clickDelay, 500); // time before a click is registered as a new sequense
    INODE_SET_METHOD(unsigned int, holdDelay, 700); // time before a click becomes a hold
    INODE_SET_METHOD(unsigned short, maxClicks, 5); // maximum number of clicks in a sequence
    
protected:
	AButt* button;

  unsigned long 
    resetStateDelay = 500, 
    timerStart = 0;
};

} //namespace empty_sensor
} //namespace esphome
