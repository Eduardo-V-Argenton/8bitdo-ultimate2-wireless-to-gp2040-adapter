# 8BitDo Ultimate 2 Wireless to GP2040 Adapter

Adapter for using an **8BitDo Ultimate 2 Wireless** controller with **GP2040-CE**.

The project uses:

- **ESP32** to connect to the controller via Bluetooth LE.
- **RP2040 / Raspberry Pi Pico** running GP2040-CE.
- **GPIO + PWM** between the ESP32 and RP2040: each button is an open-drain output that pulls the RP2040 input low, and each stick axis is a PWM signal filtered by an RC (10k / 100nF) into an RP2040 ADC.

## Architecture

```text
8BitDo Ultimate 2 Wireless
          │
         BLE
          │
        ESP32
          │
     GPIO + PWM
          │
        RP2040
       GP2040-CE
          │
         USB
          │
        Console
```

## Status

Work in progress.

Currently implemented:

- BLE connection
- HID report reading
- Buttons
- D-Pad
- Analog sticks
- Triggers
- GPIO/PWM output to the RP2040
- Release of all inputs when the controller disconnects

## Hardware

- ESP32
- Raspberry Pi Pico / RP2040
- 8BitDo Ultimate 2 Wireless
