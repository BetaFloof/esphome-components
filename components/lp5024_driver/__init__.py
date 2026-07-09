from esphome import automation
import esphome.codegen as cg
from esphome.components import output, i2c
import esphome.config_validation as cv
from esphome.types import ConfigType
from esphome.cpp_generator import MockObj
from esphome.automation import TemplateArgsType
from esphome.const import CONF_ID, CONF_BLUE, CONF_GREEN, CONF_RED, CONF_BRIGHTNESS, CONF_LIGHT_ID

DEPENDENCIES = ['i2c']

CONF_I2C_ADDR = 0x28

lp5024_driver_ns = cg.esphome_ns.namespace("lp5024_driver")
LP5024 = lp5024_driver_ns.class_("LP5024", cg.Component, i2c.I2CDevice)

CONFIG_SCHEMA = (
    cv.Schema(
        {
            cv.GenerateID(CONF_ID): cv.declare_id(LP5024),
        }
    )
    .extend(cv.COMPONENT_SCHEMA)
    .extend(i2c.i2c_device_schema(CONF_I2C_ADDR))
)

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await i2c.register_i2c_device(var, config)

LP5024SetLEDAction = lp5024_driver_ns.class_("LP5024SetLEDAction", automation.Action)
LP5024SetAllLEDAction = lp5024_driver_ns.class_("LP5024SetAllLEDAction", automation.Action)

@automation.register_action(
    "lp5024_driver.setled",
    LP5024SetLEDAction,
    cv.Schema(
        {
            cv.GenerateID():               cv.use_id(LP5024),
            cv.Required(CONF_LIGHT_ID):    cv.templatable(cv.int_range(0, 7)),
            cv.Required(CONF_RED):         cv.templatable(cv.int_range(0, 255)),
            cv.Required(CONF_GREEN):       cv.templatable(cv.int_range(0, 255)),
            cv.Required(CONF_BLUE):        cv.templatable(cv.int_range(0, 255)),
            cv.Required(CONF_BRIGHTNESS):  cv.templatable(cv.int_range(0, 255)),
        }
    ),
    synchronous=True,
)
async def lp5024_driver_set_led_to_code(config: ConfigType, action_id: MockObj, template_arg: MockObj, args: TemplateArgsType) -> MockObj:
    parent = await cg.get_variable(config[CONF_ID])
    var = cg.new_Pvariable(action_id, template_arg, parent)

    light_id_template_   = await cg.templatable(config[CONF_LIGHT_ID],   args, cg.uint8)
    red_template_        = await cg.templatable(config[CONF_RED],        args, cg.uint8)
    green_template_      = await cg.templatable(config[CONF_GREEN],      args, cg.uint8)
    blue_template_       = await cg.templatable(config[CONF_BLUE],       args, cg.uint8)
    brightness_template_ = await cg.templatable(config[CONF_BRIGHTNESS], args, cg.uint8)

    cg.add(var.set_light_id(light_id_template_))
    cg.add(var.set_red(red_template_))
    cg.add(var.set_green(green_template_))
    cg.add(var.set_blue(blue_template_))
    cg.add(var.set_brightness(brightness_template_))

    return var

@automation.register_action(
    "lp5024_driver.setallled",
    LP5024SetAllLEDAction,
    cv.Schema(
        {
            cv.GenerateID():               cv.use_id(LP5024),
            cv.Required(CONF_RED):         cv.templatable(cv.int_range(0, 255)),
            cv.Required(CONF_GREEN):       cv.templatable(cv.int_range(0, 255)),
            cv.Required(CONF_BLUE):        cv.templatable(cv.int_range(0, 255)),
            cv.Required(CONF_BRIGHTNESS):  cv.templatable(cv.int_range(0, 255)),
        }
    ),
    synchronous=True,
)
async def lp5024_driver_set_all_led_to_code(config: ConfigType, action_id: MockObj, template_arg: MockObj, args: TemplateArgsType) -> MockObj:
    parent = await cg.get_variable(config[CONF_ID])
    var = cg.new_Pvariable(action_id, template_arg, parent)

    red_template_        = await cg.templatable(config[CONF_RED],        args, cg.uint8)
    green_template_      = await cg.templatable(config[CONF_GREEN],      args, cg.uint8)
    blue_template_       = await cg.templatable(config[CONF_BLUE],       args, cg.uint8)
    brightness_template_ = await cg.templatable(config[CONF_BRIGHTNESS], args, cg.uint8)

    cg.add(var.set_red(red_template_))
    cg.add(var.set_green(green_template_))
    cg.add(var.set_blue(blue_template_))
    cg.add(var.set_brightness(brightness_template_))

    return var
