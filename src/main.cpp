#include <Arduino.h>
#include <BLEDevice.h>
#include "controller_connection.hpp"
#include "pin_mapping.hpp"
#include "debug.hpp"

void setup() {
  DEBUG_BEGIN(115200);

  BLEDevice::init("ESP32");
  set_ble_find_controller();
  connect_controller();
  setup_virtual_buttons();
}

void loop() {
  if(newReport) 
  {
    newReport = false;
    map_gamepad(gamepad, report);
    updateButtonsState(gamepad);
  }
}
