#include "esphome/core/log.h"
#include "lp5024_driver.h"

namespace esphome::lp5024_driver {

static const char *TAG = "lp5024_driver.component";

void LP5024::setup() {
    ESP_LOGD(TAG, "Setting up LP5024...");

    // Enable chip: set CHIP_EN bit in DEVICE_CONFIG0
    uint8_t device_config0 = 0x40;
    this->write_bytes(REG_DEVICE_CONFIG0, &device_config0, 1);

    // LED_CONFIG0: all 8 LEDs non-bank mode
    uint8_t led_config0 = 0x00;
    this->write_bytes(REG_LED_CONFIG0, &led_config0, 1);

    clearAllLED();
}

void LP5024::dump_config() {
    ESP_LOGCONFIG(TAG, "LP5024 Driver:");
    LOG_I2C_DEVICE(this);
    ESP_LOGCONFIG(TAG, "  light_id   = %i", this->light_id_);
    ESP_LOGCONFIG(TAG, "  red        = %i", this->red_);
    ESP_LOGCONFIG(TAG, "  green      = %i", this->green_);
    ESP_LOGCONFIG(TAG, "  blue       = %i", this->blue_);
    ESP_LOGCONFIG(TAG, "  brightness = %i", this->brightness_);
}

void LP5024::setLED() {
  uint8_t base = REG_OUT0_COLOR + (light_id_ * 3);

  // LED0 has red and green switched, probably on the pcb
  if (light_id_ == 0) {
    this->write_bytes(base,     &green_, 1);
    this->write_bytes(base + 1, &red_,   1);
    this->write_bytes(base + 2, &blue_,  1);
  }
  else {
    this->write_bytes(base,     &red_,   1);
    this->write_bytes(base + 1, &green_, 1);
    this->write_bytes(base + 2, &blue_,  1);
  }

  this->write_bytes(REG_LED0_BRIGHTNESS + light_id_, &brightness_, 1);
}

void LP5024::setAllLED() {
 for (uint8_t i = 0; i <= 7; i++) {
    set_light_id(i);
    setLED();
  }
}

void LP5024::clearAllLED() {
 for (uint8_t i = 0; i <= 7; i++) {
    set_light_id(i);
    set_red(0);
    set_green(0);
    set_blue(0);
    set_brightness(0);
    setLED();
  }
}
}  // namespace esphome::lp5024_driver
