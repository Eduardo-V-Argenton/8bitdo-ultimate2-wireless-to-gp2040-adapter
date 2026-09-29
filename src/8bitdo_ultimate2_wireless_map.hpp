#pragma once

#include <Arduino.h>

struct GamepadState
{
    bool a;
    bool b;
    bool x;
    bool y;

    bool dup;
    bool ddown;
    bool dleft;
    bool dright;
    
    bool lb;
    bool rb;

    bool lt_b;
    bool rt_b;

    uint8_t lt;
    uint8_t rt;

    bool share;
    bool options;
    bool ps;
    bool lap; // Left Analog Stick Pressed
    bool rap; // Right Analog Stick Pressed

    uint8_t lax;
    uint8_t lay;
    uint8_t rax;
    uint8_t ray;
};

void map_gamepad(GamepadState& gamepad, uint8_t* report);
void test_bool_buttons(GamepadState& gamepad);
void test_sticks(GamepadState& gamepad);
void test_triggers(GamepadState& gamepad);