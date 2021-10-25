#include "esphome/core/log.h"
#include "AButt_Sensor.h"

namespace esphome {
namespace aButt_sensor {

static const char *TAG = "aButt_sensor.AButtSensor";

void AButtSensor::setup() {
    pin_->setup();

	ESP_LOGD(TAG, "Setup completed");
}

void AButtSensor::loop() {	
	//Check the real button state
	bool pinState = pin_->digital_read();

	unsigned long now = esphome::millis();

	//Manage _isPressed var
	if (pinState != _lastState) {
		// reset the debouncing timer
		_lastDebounceTime = now;
	}

	if ((now - _lastDebounceTime) > debounce_) {
		// whatever the reading is at, it's been there for longer than the debounce
		// delay, so take it as the actual current state:
		_isPressed = pinState;
	}

	// do the callback and actual logics
	if (_isPressed) {
		if (!_wasPressed) {
			_lastPressTime = now;
		} else if (!_isHeld && now - _lastPressTime >= holdDelay_) {
			startHold();			
		}
	} else {
		if (_isHeld) {
			endHold();
		} else if (_wasPressed) {
			++clickCount;
			//start was pressed timer
			_lastClickTime = now;

			if (clickCount >= maxClicks_) {
				finishClick();
			}
		}
	}

	//if not pressed and released again within the time send the callback and number of clicks
	if (now - _lastClickTime >= clickDelay_) {
		finishClick();
	}

	// remember last states
	_lastState = pinState;
	_wasPressed = _isPressed;

	// click state reset to 0 to make sure that same state events are picked up
	// and make the history graph pretier
	float state = get_raw_state();
	if (state > 0) {
		if (timerStart_ == 0) {
			timerStart_ = now;
		}

		if (now - timerStart_ > resetStateDelay_) {
			publish_state(0); //send 0 to reset click count
			timerStart_ = 0;
		}
	}
}

void AButtSensor::dump_config() {
	ESP_LOGCONFIG(TAG, "AButt sensor");

	LOG_SENSOR("", "AButt", this);

  	LOG_PIN("  Pin: ", pin_);
	ESP_LOGCONFIG(TAG, "Debounce: %i", debounce_);
	ESP_LOGCONFIG(TAG, "ClickDelay: %i", clickDelay_);
	ESP_LOGCONFIG(TAG, "HoldDelay: %i", holdDelay_);
	ESP_LOGCONFIG(TAG, "MaxClicks: %i", maxClicks_);
}

void AButtSensor::finishClick() {
	// only do something when there where actual clicks
	if (clickCount > 0) {
		publish_state(clickCount); //publish button was clicked x times

		clickCount = 0;
	}
}

void AButtSensor::startHold() {
	// just in case there was a click before the hold finish up the clicks
	finishClick();

	_isHeld = true;
	publish_state(-1); //publish button is being held
}
void AButtSensor::endHold() {
	_isHeld = false;
	publish_state(-1); //publish button is being released
}


} //namespace empty_sensor
} //namespace esphome
