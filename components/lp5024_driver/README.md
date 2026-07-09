# LP5024 Driver
ESPHome component for the TI LP5024 LED Driver

Details from: [LP5024 LED Driver](https://www.ti.com/lit/ds/symlink/lp5024.pdf)

## Example configuration
````
i2c:
  - scl: 5
    sda: 4
    id: i2c_1

lp5024_driver:
  id: lp5024
  i2c_id: i2c_1
````

## Action examples
Set LED
````
  on_boot:
    - priority: -100
      then:
        - lp5024_driver.setled:
            light_id: 0
            red: 0
            green: 255
            blue: 0
            brightness: 255
````

Set All LEDs
````
  on_boot:
    - priority: -100
      then:
        - lp5024_driver.setallled:
            red: 0
            green: 255
            blue: 0
            brightness: 255
````
