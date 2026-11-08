#pragma once

#include <Arduino.h>

constexpr uint8_t PIN_STATUS_LED = 12;

// Blinks the reason for the last reset, then turns the LED off:
// 3 fast blinks = brownout, 2 slow = software restart (no controller,
// disconnect), 1 slow = power on, 5 fast = anything else (panic, watchdog).
void status_led_show_reset_reason();
void status_led_set(bool on);
