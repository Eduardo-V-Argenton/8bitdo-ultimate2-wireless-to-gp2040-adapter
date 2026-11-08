# 8BitDo Ultimate 2 Wireless to GP2040-CE Adapter

Use an **8BitDo Ultimate 2 Wireless** controller on a **PS4** (or PC) through **GP2040-CE**.

An ESP32 connects to the controller over Bluetooth LE, reads its HID report and drives the inputs of an RP2040 running GP2040-CE, as if the buttons and sticks were wired to it. GP2040-CE then does the console side: USB, PS4 mode and authentication.

## How it works

- **Buttons:** each of the 17 digital inputs is an open-drain output on the ESP32 that pulls the matching RP2040 input low when pressed.
- **Sticks:** each axis is an 8-bit PWM signal at 78 kHz, filtered by an RC (10k / 100nF) into one of the RP2040 ADCs (GP26–GP29).
- **PS4 authentication:** GP2040-CE forwards the console's challenge to an original DualShock 4 plugged into the RP2040 USB host port (GP0/GP1).
- **Disconnects:** if the controller drops, the ESP32 releases every input, centers the sticks and restarts to reconnect.

## Hardware

- ESP32 (NodeMCU-32S)
- RP2040 board with GP26–GP29 broken out (YD-RP2040 or similar; the official Pico has no GP29)
- 4× 10kΩ and 4× 100nF for the stick filters
- Optional: LED + 330Ω on GPIO12 for status

The KiCad schematics are in this repository.

### Wiring

| Input | ESP32 | RP2040 |
|---|---|---|
| A | GPIO13 | GP6 |
| B | GPIO14 | GP7 |
| X | GPIO16 | GP10 |
| Y | GPIO17 | GP11 |
| Up | GPIO18 | GP2 |
| Down | GPIO19 | GP3 |
| Left | GPIO21 | GP5 |
| Right | GPIO22 | GP4 |
| LB | GPIO23 | GP13 |
| RB | GPIO27 | GP12 |
| LT (digital) | GPIO4 | GP9 |
| RT (digital) | GPIO5 | GP8 |
| Share | GPIO15 | GP16 |
| Options | GPIO2 | GP17 |
| Home | GPIO0 | GP20 |
| L3 | GPIO1 | GP18 |
| R3 | GPIO3 | GP19 |
| Left stick X | GPIO25 | GP28 |
| Left stick Y | GPIO26 | GP29 |
| Right stick X | GPIO32 | GP26 |
| Right stick Y | GPIO33 | GP27 |

## GP2040-CE configuration

Tested with GP2040-CE 0.7.12. Open the web configurator (hold S2/Start while plugging in, then go to `http://192.168.7.1`):

1. **Settings:** Input Mode **PS4**, authentication **Keys**.
3. **Pin Mapping:** buttons as in the wiring table.
4. **LED Configuration:** RGB data pin = **-1**. The default puts it on GP28, which fights the left stick X filter.
5. **Add-ons → Analog:** enabled, left stick and right stick.

Then plug the DualShock 4 into the USB-A port first and the RP2040 into the PS4. Don't press PS on the DualShock 4: it would pair over Bluetooth and take over player 1.

## Building and flashing

The firmware is a [PlatformIO](https://platformio.org/) project pinned to `espressif32@6.9.0` (Arduino-ESP32 2.0.17), because the LEDC calls it uses were removed in 3.x.

```bash
pio run -t upload
```

## Status LED (optional)

With an LED + 330Ω from GPIO12 to GND, the ESP32 blinks the reason for its last reset at boot:

| Pattern | Meaning |
|---|---|
| 3 fast | Brownout (supply too weak) |
| 2 slow | Software restart (controller not found or disconnected) |
| 1 slow | Normal power on |
| 5 fast | Anything else (crash, watchdog) |

The LED stays off while scanning and turns on once the controller is connected. Never put a pull-up on GPIO12: it's a boot strap pin and the ESP32 won't boot.

## Calibration

The RP2040 ADC on the tested board reads full scale at about 3.03V instead of 3.3V, so `src/pin_mapping.hpp` rescales each axis to rest at about 1.51V and reach both ends. If the sticks don't rest at 0 or don't reach ±1 on your board (check with [gamepad-tester.com](https://gamepad-tester.com)), adjust `STICK_IN_*`, `STICK_CENTER` and `STICK_OUT_*`.

## Known limitations

- **GPIO1 and GPIO3 ** are also the ESP32 serial port. With `DEBUG_ENABLED` set in `src/debug.hpp`, Right and RT don't work.
- **GPIO2 (Options)** also drives the NodeMCU's onboard LED, so that LED lights up when Options is pressed.
- The analog triggers are sent as digital L2/R2 only.
