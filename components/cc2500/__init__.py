import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import spi
from esphome.const import CONF_ID

DEPENDENCIES = ["spi"]
CODEOWNERS = ["@rrooggiieerr"]

cc2500_ns = cg.esphome_ns.namespace("cc2500")
CC2500Component = cc2500_ns.class_("CC2500Component", cg.Component, spi.SPIDevice)
CC2500Device = cc2500_ns.class_("CC2500Device")

CONF_CC2500_ID = 'cc2500_id'
CONF_OUTPUT_POWER = 'output_power'
# CONF_SNIFF_AFTER_X_COMMANDS = 'sniff_after_x_commands'

CONFIG_SCHEMA = cv.Schema(
    {
        cv.GenerateID(): cv.declare_id(CC2500Component),
        cv.Optional(CONF_OUTPUT_POWER, default=255): cv.uint8_t,
        # cv.Optional(CONF_SNIFF_AFTER_X_COMMANDS, default=5): cv.uint16_t,
    }
).extend(cv.COMPONENT_SCHEMA).extend(spi.spi_device_schema(cs_pin_required=True))

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    if CONF_OUTPUT_POWER in config:
        cg.add(var.set_output_power(config[CONF_OUTPUT_POWER]))
    # if CONF_SNIFF_AFTER_X_COMMANDS in config:
    #     cg.add(var.set_sniff_after_x_commands(config[CONF_SNIFF_AFTER_X_COMMANDS]))
    
    await cg.register_component(var, config)
    await spi.register_spi_device(var, config)

async def register_cc2500_device(var, config):
    parent = await cg.get_variable(config[CONF_CC2500_ID])
    cg.add(var.set_parent(parent))
