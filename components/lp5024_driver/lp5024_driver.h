#pragma once

#include "esphome/core/component.h"
#include "esphome/components/i2c/i2c.h"

namespace esphome::lp5024_driver {

// LP5024 Registers
#define REG_DEVICE_CONFIG0   0x00
#define REG_DEVICE_CONFIG1   0x01
#define REG_LED_CONFIG0      0x02
#define REG_BANK_BRIGHTNESS  0x03
#define REG_BANK_A_COLOR     0x04
#define REG_BANK_B_COLOR     0x05
#define REG_BANK_C_COLOR     0x06
#define REG_LED0_BRIGHTNESS  0x07
#define REG_OUT0_COLOR       0x0F

class LP5024 : public i2c::I2CDevice, public Component {
 public:
  void setup() override;
  void dump_config() override;

  void set_light_id(uint8_t light_id) { this->light_id_ = light_id; }
  void set_red(uint8_t red) { this->red_ = red; }
  void set_green(uint8_t green) { this->green_ = green; }
  void set_blue(uint8_t blue) { this->blue_ = blue; }
  void set_brightness(uint8_t brightness) { this->brightness_ = brightness; }

  void setLED();
  void setAllLED();
  void clearAllLED();

 protected:
  uint8_t light_id_{0};
  uint8_t red_{0};
  uint8_t green_{0};
  uint8_t blue_{0};
  uint8_t brightness_{0};
};
}  // namespace esphome::lp5024_driver
