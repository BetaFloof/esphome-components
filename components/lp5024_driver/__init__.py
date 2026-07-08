from esphome import automation
import esphome.codegen as cg
from esphome.components import light, output, i2c
import esphome.config_validation as cv
from esphome.const import CONF_BLUE, CONF_GREEN, CONF_OUTPUT_ID, CONF_RED, CONF_BRIGHTNESS, CONF_LIGHT_ID

DEPENDENCIES = ['i2c']

CONF_I2C_ADDR = 0x28

lp5024_driver_ns = cg.esphome_ns.namespace("lp5024_driver")
LP5024 = lp5024_driver_ns.class_("LP5024", cg.Component, i2c.I2CDevice, light.LightOutput)

CONFIG_SCHEMA = light.RGB_LIGHT_SCHEMA.extend(
    {
        cv.GenerateID(CONF_OUTPUT_ID): cv.declare_id(LP5024),
        cv.Required(CONF_LIGHT_ID):    cv.int_range(0, 7),
        cv.Required(CONF_RED):         cv.int_range(0, 255),
        cv.Required(CONF_GREEN):       cv.int_range(0, 255),
        cv.Required(CONF_BLUE):        cv.int_range(0, 255),
        cv.Required(CONF_BRIGHTNESS):  cv.int_range(0, 255),
    }
).extend(cv.COMPONENT_SCHEMA).extend(i2c.i2c_device_schema(CONF_I2C_ADDR))

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_OUTPUT_ID])
    await light.register_light(var, config)

    yield cg.register_component(var, config)
    yield i2c.register_i2c_device(var, config)

    light_id = await cg.get_variable(config[CONF_LIGHT_ID])
    cg.add(var.set_light_id(light_id))
    red = await cg.get_variable(config[CONF_RED])
    cg.add(var.set_red(red))
    green = await cg.get_variable(config[CONF_GREEN])
    cg.add(var.set_green(green))
    blue = await cg.get_variable(config[CONF_BLUE])
    cg.add(var.set_blue(blue))
    brightness = await cg.get_variable(config[CONF_BRIGHTNESS])
    cg.add(var.set_brightness(brightness))

LP5024SetLEDAction = lp5024_driver_ns.class_("LP5024SetLEDAction", automation.Action)
LP5024SetAllLEDAction = lp5024_driver_ns.class_("LP5024SetAllLEDAction", automation.Action)

@automation.register_action(
    "lp5024.setled",
    LP5024SetLEDAction,
    cv.Schema(
        {
            cv.Required(CONF_LIGHT_ID):    cv.templatable(cv.int_range(0, 7)),
            cv.Required(CONF_RED):         cv.templatable(cv.int_range(0, 255)),
            cv.Required(CONF_GREEN):       cv.templatable(cv.int_range(0, 255)),
            cv.Required(CONF_BLUE):        cv.templatable(cv.int_range(0, 255)),
            cv.Required(CONF_BRIGHTNESS):  cv.templatable(cv.int_range(0, 255)),
        }
    ),
    synchronous=True,
)

@automation.register_action(
    "lp5024.setallled",
    LP5024SetAllLEDAction,
    cv.Schema(
        {
            cv.Required(CONF_RED):         cv.templatable(cv.int_range(0, 255)),
            cv.Required(CONF_GREEN):       cv.templatable(cv.int_range(0, 255)),
            cv.Required(CONF_BLUE):        cv.templatable(cv.int_range(0, 255)),
            cv.Required(CONF_BRIGHTNESS):  cv.templatable(cv.int_range(0, 255)),
        }
    ),
    synchronous=True,
)
