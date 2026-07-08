#include "esphome/core/log.h"
#include "lp5024_driver.h"

namespace esphome {
namespace lp5024_driver {

static const char *TAG = "lp5024_driver.component";

void LP5024::setup() {

}

void LP5024::loop() {

}

void LP5024::dump_config(){
    ESP_LOGCONFIG(TAG, "LP5024 Driver");
}


}  // namespace lp5024_driver
}  // namespace esphome
