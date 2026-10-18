#include <Arduino.h>
#include <BLEDevice.h>
#include "controller_connection.hpp"
#include "pin_mapping.hpp"
#include "debug.hpp"

void setup() {
  // Outputs first, so the RP2040 sees released buttons and centered sticks
  // while the ESP32 is still scanning. GPIO2 is PIN_OPTIONS, so it can't be
  // used as a status LED.
  setup_virtual_buttons();
  release_all_buttons();

  DEBUG_BEGIN(115200);

  BLEDevice::init("ESP32");
  set_ble_find_controller();
  connect_controller();
}

void loop() {
  if(controller_disconnected)
  {
    DEBUG_PRINTLN("Controller disconnected. Restarting");
    release_all_buttons();
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
