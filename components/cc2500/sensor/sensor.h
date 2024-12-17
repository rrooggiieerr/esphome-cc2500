#pragma once

#include "esphome/core/component.h"
#include "esphome/core/helpers.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/adc/adc_sensor.h"
#include "../cc2500.h"

namespace esphome {
namespace cc2500 {

class CC2500TemperatureSensor: public adc::ADCSensor {
public:
	void setup() override;
	void set_parent(CC2500Component *parent) { this->parent_ = parent; }
	void update();
protected:
	CC2500Component *parent_ { nullptr };
};

}  // namespace cc2500
}  // namespace esphome
