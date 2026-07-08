#include "esphome/core/log.h"
#include "lp5024_driver.h"

namespace esphome::lp5024_driver {

static const char *TAG = "lp5024_driver.component";

void LP5024::setup() {
    ESP_LOGD(TAG, "Setting up LP5024...");

    // Enable chip: set CHIP_EN bit in DEVICE_CONFIG0
    uint8_t device_config0 = 0x40;
    this->write_register(REG_DEVICE_CONFIG0, &device_config0, 1);

    // LED_CONFIG0: all 8 LEDs non-bank mode
    uint8_t led_config0 = 0x00;
    this->write_register(REG_LED_CONFIG0, &led_config0, 1);
}

void LP5024::dump_config() {
    ESP_LOGCONFIG(TAG, "LP5024 Driver");
    ESP_LOGCONFIG(TAG, "  light_id   = %i", this->light_id_);
    ESP_LOGCONFIG(TAG, "  red        = %i", this->red_);
    ESP_LOGCONFIG(TAG, "  green      = %i", this->green_);
    ESP_LOGCONFIG(TAG, "  blue       = %i", this->blue_);
    ESP_LOGCONFIG(TAG, "  brightness = %i", this->brightness_);
}

void LP5024::setLED(uint8_t light_id, uint8_t red, uint8_t green, uint8_t blue, uint8_t brightness) {
  uint8_t base = REG_OUT0_COLOR + (light_id * 3);

  // LED0 has red and green switched, probably on the pcb
  if (light_id == 0) {
    this->write_register(base,     &green, 1);
    this->write_register(base + 1, &red,   1);
    this->write_register(base + 2, &blue,  1);
  }
  else {
    this->write_register(base,     &red,   1);
    this->write_register(base + 1, &green, 1);
    this->write_register(base + 2, &blue,  1);
  }

  this->write_register(REG_LED0_BRIGHTNESS + light_id, &brightness, 1);
}

void LP5024::setAllLED(uint8_t red, uint8_t green, uint8_t blue, uint8_t brightness) {
 for (uint8_t i = 0; i <= 7; i++) {
    setLED(i, red, green, blue, brightness);
  }
}

}  // namespace esphome::lp5024_driver
