#pragma once

#include <Arduino.h>

struct GamepadState
{
    bool a; // 0
    bool b; // 1
    bool x; // 2
    bool y; // 3

    bool dup; // 4
    bool ddown; // 5
    bool dleft; // 6
    bool dright; // 7
    
    bool lb; // 8
    bool rb; // 9

    bool lt_b; // 10
    bool rt_b; // 11

    uint8_t lt; // 21
    uint8_t rt; // 22

    bool share; // 12
    bool options; // 13
    bool ps; // 14
    bool lap; // Left Analog Stick Pressed  | 15
    bool rap; // Right Analog Stick Pressed | 16 

    uint8_t lax; // 17
    uint8_t lay; // 18
    uint8_t rax; // 19
    uint8_t ray; // 20
};

void map_gamepad(GamepadState& gamepad, uint8_t* report);
void test_bool_buttons(GamepadState& gamepad);
void test_sticks(GamepadState& gamepad);
void test_triggers(GamepadState& gamepad);