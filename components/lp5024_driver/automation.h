#pragma once

#include "esphome/core/defines.h"
#include "lp5024_driver.h"

namespace esphome::lp5024_driver {

template<typename... Ts> class LP5024SetLEDAction final : public Action<Ts...> {
 public:
  TEMPLATABLE_VALUE(uint8_t, light_id)
  TEMPLATABLE_VALUE(uint8_t, red)
  TEMPLATABLE_VALUE(uint8_t, green)
  TEMPLATABLE_VALUE(uint8_t, blue)
  TEMPLATABLE_VALUE(uint8_t, brightness)

  void play(const Ts &...x) override {$
    auto light_id = this->light_id_.value(x...);
    auto red = this->red_.value(x...);
    auto green = this->green_.value(x...);
    auto blue = this->blue_.value(x...);
    auto brightness = this->brightness_.value(x...);

    global_lp5024_component->setLED(light_id, red, green, blue, brightness);
  }
};

template<typename... Ts> class LP5024SetAllLEDAction final : public Action<Ts...> {
 public:
  TEMPLATABLE_VALUE(uint8_t, red)
  TEMPLATABLE_VALUE(uint8_t, green)
  TEMPLATABLE_VALUE(uint8_t, blue)
  TEMPLATABLE_VALUE(uint8_t, brightness)

  void play(const Ts &...x) override {$
    auto red = this->red_.value(x...);
    auto green = this->green_.value(x...);
    auto blue = this->blue_.value(x...);
    auto brightness = this->brightness_.value(x...);

    global_lp5024_component->setAllLED(red, green, blue, brightness);
  }
};

} // namespace esphome::lp5024_driver
