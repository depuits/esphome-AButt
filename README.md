# Esphome AButt custom component

Custom component for [esphome](https://esphome.io/) which aims to have a simplified multiclick button component in place of the [binary sensor on multiclick](https://esphome.io/components/binary_sensor/index.html?highlight=binar#binary-sensor-on-multi-click). This implementation uses the [AButt library](https://github.com/depuits/AButt).

## Instalation

Clone this repository into custom_components in a folder where the device config.yaml is stored.

    git clone https://github.com/depuits/esphome-AButt.git AButt

## Usage

Button presses are registered as a value change with. The value reporterd is the number of time the butten was clicked in sequence. So a single press will report 1, double click will report 2, tripple click 3 and so on to the maximum defined clicks. When the button is pressed and hold the sensor will report -1 and 0 when it's released again.

### Example

```
sensor:
  - platform: AButt
    name: "Button"
    retain: False # don't retain mqtt messages
    inverted: True
    pin: 0
    debounce: 50
    on_value:
      then:
        - if:
            condition:
              lambda: 'return x == 1;'
            then:
              - light.toggle: wall
        - if:
            condition:
              lambda: 'return x == 2;'
            then:
              - light.toggle: ceiling

        # add conditions like you wish
        # -1 = hold
        #  0 = release
        # any other number is the number of presses to the max defined

```

### Options

| Option     | Description                                                                                 | Required | Default value |
|------------|---------------------------------------------------------------------------------------------|----------|---------------|
| pin        | Pin conected to the button                                                                  | x        |               |
| inverted   | Invert to logic level                                                                       |          | false         |
| isDigital  | Set to false when using an analog input                                                     |          | true          |
| debounce   | Amount of ms before a press is registered                                                   |          | 50            |
| clickDelay | Ms before a click is registered as a new sequense                                           |          | 500           |
| holdDelay  | Time before a click is registered as hold                                                   |          | 700           |
| maxClicks  | Maximum number of clicks in a sequence (after this amount a new sequence is always started) |          | 5             |


## Example of same behavior with binary_sensor