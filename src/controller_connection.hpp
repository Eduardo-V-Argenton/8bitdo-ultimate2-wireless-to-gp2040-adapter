#pragma once

#include <Arduino.h>
#include "8bitdo_ultimate2_wireless_map.hpp"

extern GamepadState gamepad;
extern uint8_t report[33];
extern bool newReport;

void set_ble_find_controller();
void connect_controller();