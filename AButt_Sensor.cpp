#include "esphome/core/log.h"
#include "AButt_Sensor.h"
#include "AButt.h"

namespace esphome {
namespace aButt_sensor {

static const char *TAG = "aButt_sensor.AButtSensor";

void clicked(AButt* sender, unsigned short clicks) {
	reinterpret_cast<AButtSensor*>(sender->getData())->publish_state(clicks);
}

void holdStart(AButt* sender) {
	reinterpret_cast<AButtSensor*>(sender->getData())->publish_state(-1);
}
void holdEnd(AButt* sender) {
	reinterpret_cast<AButtSensor*>(sender->getData())->publish_state(0);
}

void AButtSensor::setup() {
	button = new AButt(pin_, inverted_, isDigital_, debounce_);
	button->setData(this);

	button->setClickDelay(clickDelay_);
	button->setHoldDelay(holdDelay_);
	button->setMaxClicks(maxClicks_);

	if (inverted_) {
		pinMode(pin_, INPUT_PULLUP);
	} else {
		pinMode(pin_, INPUT);
	}

	button->onClick(clicked);
	button->onHold(holdStart, holdEnd);

	ESP_LOGCONFIG(TAG, "Setup completed");
}

void AButtSensor::loop() {
	button->update();
}

void AButtSensor::dump_config() {
    ESP_LOGCONFIG(TAG, "AButt sensor");

	ESP_LOGD(TAG, "Pin: %i", pin_);
	ESP_LOGD(TAG, "Inverted: %d", inverted_);
	ESP_LOGD(TAG, "IsDigital: %d", isDigital_);
	ESP_LOGD(TAG, "Debounce: %i", debounce_);
	ESP_LOGD(TAG, "ClickDelay: %i", clickDelay_);
	ESP_LOGD(TAG, "HoldDelay: %i", holdDelay_);
	ESP_LOGD(TAG, "MaxClicks: %i", maxClicks_);
}

} //namespace empty_sensor
} //namespace esphome
