#include <Arduino.h>
#include <BLEDevice.h>
#include "controller_connection.hpp"
#include "pin_mapping.hpp"
#include "debug.hpp"

void setup() {
  pinMode(2, OUTPUT);

  for (int i = 0; i < 5; i++) 
  {
    digitalWrite(2, HIGH);
    delay(200);
    digitalWrite(2, LOW);
    delay(200);
  }
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
    updateControllerState(gamepad);
  }
}
