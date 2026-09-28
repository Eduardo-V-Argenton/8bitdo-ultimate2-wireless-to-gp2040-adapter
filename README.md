# 8BitDo Ultimate 2 Wireless to GP2040 Adapter

Adapter for using an **8BitDo Ultimate 2 Wireless** controller with **GP2040-CE**.

The project uses:

- **ESP32** to connect to the controller via Bluetooth LE.
- **RP2040 / Raspberry Pi Pico** running GP2040-CE.
- **UART** for communication between the ESP32 and RP2040.

## Architecture

```text
8BitDo Ultimate 2 Wireless
          │
         BLE
          │
        ESP32
          │
         UART
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
- UART communication

## Hardware

- ESP32
- Raspberry Pi Pico / RP2040
- 8BitDo Ultimate 2 Wireless
