#pragma once

#include <stdint.h>

struct KnownDevice {
    uint8_t addr;
    const char *name;
};

static const KnownDevice KNOWN_DEVICES[] = {
    {0x1E, "HMC5883L / QMC5883L magnetometer"},
    {0x20, "PCF8574 / MCP23017"},
    {0x21, "PCF8574 / MCP23017"},
    {0x22, "PCF8574 / MCP23017"},
    {0x23, "PCF8574 / BH1750 light"},
    {0x24, "PCF8574 / MCP23017"},
    {0x25, "PCF8574 / MCP23017"},
    {0x26, "PCF8574 / MCP23017"},
    {0x27, "PCF8574 / LCD1602 backpack"},
    {0x38, "PCF8574A / AHT10"},
    {0x39, "PCF8574A / TSL2561"},
    {0x3A, "PCF8574A"},
    {0x3B, "PCF8574A"},
    {0x3C, "SSD1306 OLED"},
    {0x3D, "SSD1306 OLED"},
    {0x3E, "PCF8574A"},
    {0x3F, "PCF8574A / LCD2004 backpack"},
    {0x40, "INA219 / HTU21D / SI7021"},
    {0x48, "ADS1115 / TMP102"},
    {0x49, "ADS1115"},
    {0x4A, "ADS1115"},
    {0x4B, "ADS1115"},
    {0x50, "AT24Cxx EEPROM"},
    {0x51, "AT24Cxx EEPROM"},
    {0x52, "AT24Cxx EEPROM"},
    {0x53, "AT24Cxx EEPROM / ADXL345"},
    {0x54, "AT24Cxx EEPROM"},
    {0x55, "AT24Cxx EEPROM"},
    {0x56, "AT24Cxx EEPROM"},
    {0x57, "AT24Cxx EEPROM / MAX30102"},
    {0x5A, "MLX90614 IR thermometer"},
    {0x68, "MPU6050 / DS3231 / DS1307"},
    {0x69, "MPU6050 (AD0=1)"},
    {0x70, "TCA9548A mux"},
    {0x76, "BME280 / BMP280"},
    {0x77, "BME280 / BMP280 (SDO=1)"},
};

static const size_t KNOWN_DEVICES_COUNT =
    sizeof(KNOWN_DEVICES) / sizeof(KNOWN_DEVICES[0]);

inline const char *lookupKnownDevice(uint8_t addr) {
    for (size_t i = 0; i < KNOWN_DEVICES_COUNT; ++i) {
        if (KNOWN_DEVICES[i].addr == addr) {
            return KNOWN_DEVICES[i].name;
        }
    }
    return "--";
}
