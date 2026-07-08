#pragma once

#include "esphome/core/component.h"
#include "esphome/components/i2c/i2c.h"

namespace esphome {
namespace lp5024_driver {

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
  void loop() override;
  void dump_config() override;
};


}  // namespace lp5024_driver
}  // namespace esphome
