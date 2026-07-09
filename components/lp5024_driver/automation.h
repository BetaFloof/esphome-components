#pragma once

#include "esphome/core/defines.h"
#include "lp5024_driver.h"

namespace esphome::lp5024_driver {

template<typename... Ts> class LP5024SetLEDAction final : public Action<Ts...> {
 public:
  explicit LP5024SetLEDAction(LP5024 *parent) : parent_(parent) {}
  TEMPLATABLE_VALUE(uint8_t, light_id)
  TEMPLATABLE_VALUE(uint8_t, red)
  TEMPLATABLE_VALUE(uint8_t, green)
  TEMPLATABLE_VALUE(uint8_t, blue)
  TEMPLATABLE_VALUE(uint8_t, brightness)

  void play(const Ts &...x) override {
    this->parent_->set_light_id(this->light_id_.value(x...));
    this->parent_->set_red(this->red_.value(x...));
    this->parent_->set_green(this->green_.value(x...));
    this->parent_->set_blue(this->blue_.value(x...));
    this->parent_->set_brightness(this->brightness_.value(x...));

    this->parent_->setLED();

  }
 protected:
  LP5024 *parent_;
};

template<typename... Ts> class LP5024SetAllLEDAction final : public Action<Ts...> {
 public:
  explicit LP5024SetAllLEDAction(LP5024 *parent) : parent_(parent) {}
  TEMPLATABLE_VALUE(uint8_t, red)
  TEMPLATABLE_VALUE(uint8_t, green)
  TEMPLATABLE_VALUE(uint8_t, blue)
  TEMPLATABLE_VALUE(uint8_t, brightness)

  void play(const Ts &...x) override {
    this->parent_->set_red(this->red_.value(x...));
    this->parent_->set_green(this->green_.value(x...));
    this->parent_->set_blue(this->blue_.value(x...));
    this->parent_->set_brightness(this->brightness_.value(x...));

    this->parent_->setAllLED();
  }
 protected:
  LP5024 *parent_;
};
} // namespace esphome::lp5024_driver
