import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import adc, spi
from esphome import pins
from esphome.const import CONF_ID, CONF_NUMBER
from esphome.core import CORE

DEPENDENCIES = ["spi"]
CODEOWNERS = ["@rrooggiieerr"]

cc2500_ns = cg.esphome_ns.namespace("cc2500")
CC2500Component = cc2500_ns.class_("CC2500Component", cg.Component, spi.SPIDevice)
CC2500Device = cc2500_ns.class_("CC2500Device")

CONF_CC2500_ID = 'cc2500_id'
CONF_GDO0_PIN = 'gdo0_pin'
CONF_GDO2_PIN = 'gdo2_pin'
CONF_OUTPUT_POWER = 'output_power'
# CONF_SNIFF_AFTER_X_COMMANDS = 'sniff_after_x_commands'

def validate_gdo2_pin(value):
    value = pins.internal_gpio_input_pin_schema(value)
    if CORE.is_esp8266 and value[CONF_NUMBER] >= 16:
        raise cv.Invalid(
            "Pins GPIO16 and GPIO17 cannot be used as receive interrupt pin on ESP8266."
        )
    return value

CONFIG_SCHEMA = cv.Schema(
    {
        cv.GenerateID(): cv.declare_id(CC2500Component),
        cv.Optional(CONF_GDO0_PIN): adc.validate_adc_pin,
        cv.Optional(CONF_GDO2_PIN): validate_gdo2_pin,
        cv.Optional(CONF_OUTPUT_POWER, default=255): cv.uint8_t,
        # cv.Optional(CONF_SNIFF_AFTER_X_COMMANDS, default=5): cv.uint16_t,
    }
).extend(cv.COMPONENT_SCHEMA).extend(spi.spi_device_schema(cs_pin_required=True))

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    if CONF_GDO0_PIN in config:
        pin = await cg.gpio_pin_expression(config[CONF_GDO0_PIN])
        cg.add(var.set_gdo0_pin(pin))
    if CONF_GDO2_PIN in config:
        pin = await cg.gpio_pin_expression(config[CONF_GDO2_PIN])
        cg.add(var.set_gdo2_pin(pin))
    if CONF_OUTPUT_POWER in config:
        cg.add(var.set_output_power(config[CONF_OUTPUT_POWER]))
    # if CONF_SNIFF_AFTER_X_COMMANDS in config:
    #     cg.add(var.set_sniff_after_x_commands(config[CONF_SNIFF_AFTER_X_COMMANDS]))
    
    await cg.register_component(var, config)
    await spi.register_spi_device(var, config)

# A schema to use for all CC2500 devices, all CC2500 integrations must extend this!
CC2500_DEVICE_SCHEMA = cv.Schema(
    {
        cv.GenerateID(CONF_CC2500_ID): cv.use_id(CC2500Component),
    }
)

async def register_cc2500_device(var, config):
    parent = await cg.get_variable(config[CONF_CC2500_ID])
    cg.add(var.set_parent(parent))
