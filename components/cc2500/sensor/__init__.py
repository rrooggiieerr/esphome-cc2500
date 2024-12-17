import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import adc, sensor
from esphome.components.adc import sensor as adc_sensor
from esphome.const import CONF_ID, ENTITY_CATEGORY_DIAGNOSTIC, UNIT_CELSIUS,\
    DEVICE_CLASS_TEMPERATURE, STATE_CLASS_MEASUREMENT, CONF_FILTERS

from .. import (
    CC2500_DEVICE_SCHEMA,
    cc2500_ns,
    register_cc2500_device,
)

DEPENDENCIES = ["cc2500"]
CODEOWNERS = ["@rrooggiieerr"]
AUTO_LOAD = ["adc", "voltage_sampler"]

CONF_TEMPERATURE_VALUE = "temperature"

CC2500TemperatureSensor = cc2500_ns.class_(
    "CC2500TemperatureSensor", sensor.Sensor, cg.PollingComponent, adc_sensor.ADCSensor
)

CONFIG_SCHEMA = cv.All(
    cv.Schema(
        {
            cv.Optional(CONF_TEMPERATURE_VALUE): sensor.sensor_schema(
                CC2500TemperatureSensor,
                unit_of_measurement=UNIT_CELSIUS,
                accuracy_decimals=2,
                device_class=DEVICE_CLASS_TEMPERATURE,
                state_class=STATE_CLASS_MEASUREMENT,
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ).extend(cv.polling_component_schema("60s")), #.extend({cv.Optional(CONF_FILTERS): sensor.validate_filters}),
        }
    ).extend(CC2500_DEVICE_SCHEMA),
    cv.has_at_least_one_key(CONF_TEMPERATURE_VALUE)
)


async def to_code(config):
    if temperature_config := config.get(CONF_TEMPERATURE_VALUE):
        var = await sensor.new_sensor(temperature_config)
        await cg.register_component(var, temperature_config)
        await register_cc2500_device(var, config)
        await sensor.register_sensor(var, temperature_config)
