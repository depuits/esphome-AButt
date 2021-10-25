import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import sensor
from esphome.const import CONF_ID, ICON_EMPTY
from esphome import pins

aButt_sensor_ns = cg.esphome_ns.namespace('aButt_sensor')

AButtSensor = aButt_sensor_ns.class_('AButtSensor', cg.Component)

CONF_PIN = 'pin'
CONF_DEBOUNCE = 'debounce'

CONF_CLICKDELAY = 'clickDelay'
CONF_HOLDDELAY = 'holdDelay'
CONF_MAXCLICKS = 'maxClicks'

CONFIG_SCHEMA = sensor.sensor_schema('clicks', ICON_EMPTY, 0).extend({
    cv.GenerateID(): cv.declare_id(AButtSensor),
    cv.Required(CONF_PIN): pins.gpio_output_pin_schema,
    cv.Optional(CONF_DEBOUNCE, default=50): cv.positive_int,

    cv.Optional(CONF_CLICKDELAY, default=500): cv.positive_not_null_int,
    cv.Optional(CONF_HOLDDELAY, default=700): cv.positive_not_null_int,
    cv.Optional(CONF_MAXCLICKS, default=5): cv.positive_not_null_int,
}).extend(cv.COMPONENT_SCHEMA)

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await sensor.register_sensor(var, config)

    pin = await gpio_pin_expression(config[CONF_PIN])
    cg.add(var.set_pin(pin))

    cg.add(var.set_debounce(config[CONF_DEBOUNCE]))

    cg.add(var.set_clickDelay(config[CONF_CLICKDELAY]))
    cg.add(var.set_holdDelay(config[CONF_HOLDDELAY]))
    cg.add(var.set_maxClicks(config[CONF_MAXCLICKS]))
    