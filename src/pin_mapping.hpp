#pragma once

#include <Arduino.h>

constexpr uint8_t PIN_A       = 13;
constexpr uint8_t PIN_B       = 14;
constexpr uint8_t PIN_X       = 16;
constexpr uint8_t PIN_Y       = 17;

constexpr uint8_t PIN_UP      = 18;
constexpr uint8_t PIN_DOWN    = 19;
constexpr uint8_t PIN_LEFT    = 21;
constexpr uint8_t PIN_RIGHT   = 22;

constexpr uint8_t PIN_LB      = 23;
constexpr uint8_t PIN_RB      = 27;

constexpr uint8_t PIN_LT      = 4;
constexpr uint8_t PIN_RT      = 5;

constexpr uint8_t PIN_SHARE   = 15;
constexpr uint8_t PIN_OPTIONS = 2;
constexpr uint8_t PIN_PS      = 0;

constexpr uint8_t PIN_L3      = 1;
constexpr uint8_t PIN_R3      = 3;

constexpr uint8_t PIN_RX      = 32; 
constexpr uint8_t PIN_RY      = 33;

constexpr uint8_t PIN_LX      = 25;
constexpr uint8_t PIN_LY      = 26;


constexpr uint8_t buttonPins[] = {
    PIN_A,
    PIN_B,
    PIN_X,
    PIN_Y,
    PIN_UP,
    PIN_DOWN,
    PIN_LEFT,
    PIN_RIGHT,
    PIN_LB,
    PIN_RB,
    PIN_LT,
    PIN_RT,
    PIN_SHARE,
    PIN_OPTIONS,
    PIN_PS,
    PIN_L3,
    PIN_R3
};

constexpr uint8_t stickPins[] = {
    PIN_RX,
    PIN_RY,
    PIN_LX,
    PIN_LY
};

// 80 MHz / 2^8 = 312.5 kHz is the LEDC limit at 8 bits. 78.125 kHz cuts the
// ripple after the 10k/100nF filter to a quarter of what 20 kHz gives.
constexpr uint32_t STICK_PWM_FREQ = 78125;
constexpr uint8_t  STICK_PWM_BITS = 8;

// Measured on the board: the 8BitDo axes swing 0.16V / 1.70V / 3.31V
// (min / rest / max) at the ESP32 output, i.e. about 12 / 131 / 255 in
// report units.
constexpr uint8_t  STICK_IN_MIN    = 12;
constexpr uint8_t  STICK_IN_CENTER = 131;
constexpr uint8_t  STICK_IN_MAX    = 255;

// The RP2040 ADC on this board reads full scale at about 3.03V, not 3.3V
// (1.70V read as +0.12). Center the output on that range and overshoot a
// little at the ends so both directions reach full deflection.
constexpr uint8_t  STICK_CENTER    = 117;  // ~1.51V, half of the ADC range
constexpr uint8_t  STICK_OUT_MIN   = 0;
constexpr uint8_t  STICK_OUT_MAX   = 240;  // ~3.11V, past ADC full scale

void setup_virtual_buttons();
void release_all_buttons();
void updateControllerState(GamepadState& gamepad);