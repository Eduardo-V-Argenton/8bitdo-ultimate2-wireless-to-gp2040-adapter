#include <Arduino.h>
#include <BLEDevice.h>
#include "controller_connection.hpp"
#include "pin_mapping.hpp"
#include "debug.hpp"
#include "status_led.hpp"

void setup() {
  // Lower CPU clock to cut current draw. BLE works fine at 80 MHz.
  setCpuFrequencyMhz(80);

  // Outputs first, so the RP2040 sees released buttons and centered sticks
  // while the ESP32 is still scanning. GPIO2 is PIN_OPTIONS, so it can't be
  // used as a status LED.
  setup_virtual_buttons();
  release_all_buttons();

  DEBUG_BEGIN(115200);

  // Shows why the ESP32 last reset; a boot loop repeats this pattern.
  status_led_show_reset_reason();

  BLEDevice::init("ESP32");
  // Lower TX power to reduce the current spikes that can brown out a weak
  // supply. The controller sits right next to the adapter.
  BLEDevice::setPower(ESP_PWR_LVL_N0, ESP_BLE_PWR_TYPE_DEFAULT);
  BLEDevice::setPower(ESP_PWR_LVL_N0, ESP_BLE_PWR_TYPE_SCAN);
  BLEDevice::setPower(ESP_PWR_LVL_N0, ESP_BLE_PWR_TYPE_ADV);

  set_ble_find_controller();
  connect_controller();

  // Solid on: connected to the controller.
  status_led_set(true);
}

void loop() {
  if(controller_disconnected)
  {
    DEBUG_PRINTLN("Controller disconnected. Restarting");
    release_all_buttons();
    status_led_set(false);
    delay(100);
    ESP.restart();
  }

  uint8_t current[REPORT_SIZE];
  if(take_report(current))
  {
    map_gamepad(gamepad, current);
    updateControllerState(gamepad);
  }
}
