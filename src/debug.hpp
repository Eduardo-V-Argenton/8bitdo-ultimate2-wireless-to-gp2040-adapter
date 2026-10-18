#pragma once

#include <Arduino.h>

// Serial uses GPIO1 (TX) and GPIO3 (RX), which are also PIN_L3 and PIN_R3.
// With debug enabled, L3/R3 don't work and serial output toggles L3.
#define DEBUG_ENABLED 0

#if DEBUG_ENABLED

#define DEBUG_BEGIN(baud)    Serial.begin(baud)
#define DEBUG_PRINT(x)       Serial.print(x)
#define DEBUG_PRINTLN(x)     Serial.println(x)
#define DEBUG_PRINTF(...)    Serial.printf(__VA_ARGS__)

#else

#define DEBUG_BEGIN(baud)
#define DEBUG_PRINT(x)
#define DEBUG_PRINTLN(x)
#define DEBUG_PRINTF(...)

#endif