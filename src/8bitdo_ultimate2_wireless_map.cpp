#include <Arduino.h>
#include "8bitdo_ultimate2_wireless_map.hpp"

void map_gamepad(GamepadState& gamepad, uint8_t* report)
{
    gamepad.a = report[7] & 0x01;
    gamepad.b = report[7] & 0x02;
    gamepad.x = report[7] & 0x08;
    gamepad.y = report[7] & 0x10;

    uint8_t dpad = report[0];
    gamepad.dup = dpad == 0x00 || dpad == 0x01 || dpad == 0x07;
    gamepad.ddown = dpad == 0x03 || dpad == 0x04 || dpad == 0x05;
    gamepad.dright = dpad == 0x01 || dpad == 0x02 || dpad == 0x03;
    gamepad.dleft = dpad == 0x05 || dpad == 0x06 || dpad == 0x07;

    gamepad.lax = report[1];
    gamepad.lay = report[2];
    gamepad.rax = report[3];
    gamepad.ray = report[4];
    

    gamepad.rb = report[7] & 0x80;
    gamepad.lb = report[7] & 0x40;
    
    gamepad.rt = report[5];
    gamepad.lt = report[6];
    
    gamepad.rt_b = report[8] & 0x02;
    gamepad.lt_b = report[8] & 0x01;
    
    gamepad.share  = report[8] & 0x04;
    gamepad.options = report[8] & 0x08;
    gamepad.ps     = report[8] & 0x10;
    
    gamepad.rap     = report[8] & 0x40;
    gamepad.lap    = report[8] & 0x20;
}

void test_bool_buttons(GamepadState& gamepad)
{
    if(gamepad.a){Serial.println("A");}
    if(gamepad.b){Serial.println("B");}
    if(gamepad.x){Serial.println("X");}
    if(gamepad.y){Serial.println("Y");}
    if(gamepad.lb){Serial.println("LB");}
    if(gamepad.rb){Serial.println("RB");}
    if(gamepad.lt_b){Serial.println("LT");}
    if(gamepad.rt_b){Serial.println("RT");}
    if(gamepad.share){Serial.println("SHARE");}
    if(gamepad.options){Serial.println("OPTIONS");}
    if(gamepad.ps){Serial.println("PS");}
    if(gamepad.rap){Serial.println("RAP");}
    if(gamepad.lap){Serial.println("LAP");}
    if(gamepad.dup){Serial.println("UP");}
    if(gamepad.ddown){Serial.println("DOWN");}
    if(gamepad.dleft){Serial.println("LEFT");}
    if(gamepad.dright){Serial.println("RIGHT");}
}

void test_sticks(GamepadState& gamepad)
{
    Serial.printf("LX:%3u LY:%3u RX:%3u RY:%3u\n",
        gamepad.lax,
        gamepad.lay,
        gamepad.rax,
        gamepad.ray
    );
}

void test_triggers(GamepadState& gamepad)
{
    Serial.printf("RT:%d LT:%d\n",
        gamepad.rt,
        gamepad.lt
    );
}