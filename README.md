# Esphome AButt custom component


## Example

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

## Options
