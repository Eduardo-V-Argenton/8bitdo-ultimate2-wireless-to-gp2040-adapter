#include <Arduino.h>
#include "8bitdo_ultimate2_wireless_map.hpp"
#include "pin_mapping.hpp"

void setup_virtual_buttons()
{
    size_t count = sizeof(buttonPins) / sizeof(buttonPins[0]);
    for (size_t i = 0; i < count; i++) {
        pinMode(buttonPins[i], OUTPUT_OPEN_DRAIN);
        digitalWrite(buttonPins[i], HIGH);
    }

    ledcSetup(0, STICK_PWM_FREQ, STICK_PWM_BITS);
    ledcAttachPin(PIN_RX, 0);

    ledcSetup(1, STICK_PWM_FREQ, STICK_PWM_BITS);
    ledcAttachPin(PIN_RY, 1);
    
    
    ledcSetup(2, STICK_PWM_FREQ, STICK_PWM_BITS);
    ledcAttachPin(PIN_LX, 2);

    ledcSetup(3, STICK_PWM_FREQ, STICK_PWM_BITS);
    ledcAttachPin(PIN_LY, 3);
}

void release_all_buttons()
{
    size_t count = sizeof(buttonPins) / sizeof(buttonPins[0]);
    for (size_t i = 0; i < count; i++) {
        digitalWrite(buttonPins[i], HIGH);
    }

    for (uint8_t channel = 0; channel < 4; channel++) {
        ledcWrite(channel, STICK_CENTER);
    }
}

void set_virtual_button(uint8_t pin, bool pressed)
{
    digitalWrite(pin, pressed ? LOW : HIGH);
}

void updateControllerState(GamepadState& gamepad)
{
    set_virtual_button(PIN_A, gamepad.a);
    set_virtual_button(PIN_B, gamepad.b);
    set_virtual_button(PIN_X, gamepad.x);
    set_virtual_button(PIN_Y, gamepad.y);

    set_virtual_button(PIN_UP, gamepad.dup);
    set_virtual_button(PIN_DOWN, gamepad.ddown);
    set_virtual_button(PIN_LEFT, gamepad.dleft);
    set_virtual_button(PIN_RIGHT, gamepad.dright);

    set_virtual_button(PIN_LB, gamepad.lb);
    set_virtual_button(PIN_RB, gamepad.rb);

    set_virtual_button(PIN_LT, gamepad.lt_b);
    set_virtual_button(PIN_RT, gamepad.rt_b);

    set_virtual_button(PIN_SHARE, gamepad.share);
    set_virtual_button(PIN_OPTIONS, gamepad.options);
    set_virtual_button(PIN_PS, gamepad.ps);

    set_virtual_button(PIN_L3, gamepad.lap);
    set_virtual_button(PIN_R3, gamepad.rap);
    ledcWrite(2, gamepad.lax);
    ledcWrite(3, gamepad.lay);

    ledcWrite(0, gamepad.rax);
    ledcWrite(1, gamepad.ray);
}