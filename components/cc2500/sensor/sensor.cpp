#include "esphome/core/log.h"
#include "sensor.h"

#include <cinttypes>

namespace esphome {
namespace cc2500 {

static const char *const TAG = "cc2500.sensor";

void CC2500TemperatureSensor::setup() {
	ESP_LOGCONFIG(TAG, "Setting up C2500 temperature sensor...");
	this->set_pin(this->parent_->get_gdo0_pin());
	ADCSensor::setup();
}

void CC2500TemperatureSensor::update() {
	float value_v = this->sample();
	ESP_LOGV(TAG, "'%s': Got voltage=%.4fV", this->get_name().c_str(), value_v);
#ifdef USE_ESP8266
	value_v *= 3.3f;
#endif
	value_v *= 3/3.3;
	float temperature = (value_v - 0.750f) / 0.00243;
	ESP_LOGV(TAG, "'%s': Got temperature=%.4f°C", this->get_name().c_str(), temperature);
	this->publish_state(temperature);
}

}  // namespace cc2500
}  // namespace esphome
