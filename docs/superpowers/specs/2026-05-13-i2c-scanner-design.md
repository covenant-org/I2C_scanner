# I2C Scanner (ESP32) — Design Spec

**Date:** 2026-05-13
**Target:** ESP32 DevKit v1, Arduino framework via PlatformIO

## Goal

Project that scans the I2C bus on demand and reports which 7-bit
addresses respond, including a friendly name when the address matches a
well-known device.

## Hardware

- Board: ESP32 DevKit v1 (`board = esp32dev`)
- I2C pins: SDA = GPIO21, SCL = GPIO22 (Arduino-ESP32 defaults)
- Bus speed: 100 kHz (standard mode)
- External pull-ups: 4.7 kΩ to 3.3 V on SDA and SCL (user-supplied)

## File Layout

```
I2C_scanner/
├── platformio.ini
├── include/known_devices.h
├── src/main.cpp
└── README.md
```

## Behavior

1. On boot:
   - Initialize `Serial` at 115200 baud.
   - `Wire.begin(21, 22)`; `Wire.setClock(100000)`.
   - Print banner + command help.
2. Loop reads one byte at a time from `Serial`:
   - `s` → run `scanI2C()`
   - `h` or `?` → print help
   - any other printable char → print "comando desconocido, pulsa h"
   - whitespace / control chars → ignored
3. `scanI2C()`:
   - Iterates `addr` from `0x03` to `0x77`.
   - `Wire.beginTransmission(addr); err = Wire.endTransmission();`
   - `err == 0` → device ACKed, look up name in `known_devices.h`,
     print row.
   - `err == 4` → bus error, print `0xNN: error de bus`.
   - other errors → silently skip.
   - Prints total at end. If 0, hints to check wiring + pull-ups.

## Output Format

Header on every scan:
```
HEX   DEC   Dispositivo
----  ----  ------------------
```
Rows: `0x3C   60   SSD1306 OLED`. Unknown addresses print `--` as name.

## Known Devices Table

Static `const` array in `include/known_devices.h`. Entries:

| Addr(s) | Name |
|---|---|
| 0x20–0x27 | PCF8574 |
| 0x38–0x3F | PCF8574A |
| 0x3C, 0x3D | SSD1306 OLED |
| 0x40 | INA219 / HTU21D |
| 0x48–0x4B | ADS1115 |
| 0x50–0x57 | AT24Cxx EEPROM |
| 0x57 | MAX30102 |
| 0x68 | MPU6050 / DS3231 |
| 0x69 | MPU6050 (AD0=1) |
| 0x76, 0x77 | BME280 / BMP280 |

Lookup is linear; table is small enough that a binary search is
unnecessary.

## Error Cases

- Stuck bus (SDA held low) → not auto-recovered in v1; README documents
  manual recovery.
- Address collisions (e.g., 0x68 = MPU6050 or DS3231) → name string
  lists both separated by `/`.

## Verification (manual)

1. `pio run` compiles cleanly.
2. `pio run -t upload` flashes the DevKit.
3. `pio device monitor -b 115200` shows banner + prompt.
4. Empty bus → `s` reports 0 devices.
5. One known device wired with pull-ups → `s` reports its hex/dec/name.
6. Invalid command → "comando desconocido".

## Out of Scope (v1)

- 10-bit I2C addresses.
- Second I2C bus (`Wire1`).
- Bus recovery / hot-plug detection.
- Web UI / WiFi reporting.
- Automated tests (firmware, no host-side harness).
