#include <Arduino.h>
#include <esp_system.h>
#include "status_led.hpp"

static void blink(uint8_t times, uint16_t on_ms, uint16_t off_ms)
{
    for (uint8_t i = 0; i < times; i++) {
        digitalWrite(PIN_STATUS_LED, HIGH);
        delay(on_ms);
        digitalWrite(PIN_STATUS_LED, LOW);
        delay(off_ms);
    }
}

void status_led_show_reset_reason()
{
    pinMode(PIN_STATUS_LED, OUTPUT);
    digitalWrite(PIN_STATUS_LED, LOW);

    switch (esp_reset_reason()) {
        case ESP_RST_BROWNOUT:
            blink(3, 80, 80);
            break;
        case ESP_RST_SW:
            blink(2, 300, 300);
            break;
        case ESP_RST_POWERON:
            blink(1, 300, 300);
            break;
        default:
            blink(5, 80, 80);
            break;
    }
}

void status_led_set(bool on)
{
    digitalWrite(PIN_STATUS_LED, on ? HIGH : LOW);
}
