#pragma once

#include <Arduino.h>
#include "8bitdo_ultimate2_wireless_map.hpp"

constexpr size_t REPORT_SIZE = 33;
// Highest byte index read by map_gamepad() is 8.
constexpr size_t REPORT_MIN_SIZE = 9;

extern GamepadState gamepad;
extern volatile bool controller_disconnected;

void set_ble_find_controller();
void connect_controller();
bool take_report(uint8_t* out);
