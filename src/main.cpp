#include <Arduino.h>
#include <Wire.h>

#include "known_devices.h"

#ifndef I2C_SDA_PIN
#define I2C_SDA_PIN 21
#endif
#ifndef I2C_SCL_PIN
#define I2C_SCL_PIN 22
#endif
#ifndef I2C_CLOCK_HZ
#define I2C_CLOCK_HZ 100000
#endif

static void printHelp() {
    Serial.println();
    Serial.println(F("I2C Scanner (ESP32)"));
    Serial.print(F("  SDA="));
    Serial.print(I2C_SDA_PIN);
    Serial.print(F(" SCL="));
    Serial.print(I2C_SCL_PIN);
    Serial.print(F(" @ "));
    Serial.print(I2C_CLOCK_HZ / 1000);
    Serial.println(F(" kHz"));
    Serial.println(F("Comandos:"));
    Serial.println(F("  s : escanear bus I2C"));
    Serial.println(F("  h : ayuda"));
    Serial.print(F("> "));
}

static void scanI2C() {
    Serial.println();
    Serial.println(F("Escaneando 0x03..0x77 ..."));
    Serial.println(F("HEX   DEC   Dispositivo"));
    Serial.println(F("----  ----  ------------------"));

    uint8_t found = 0;
    for (uint8_t addr = 0x03; addr <= 0x77; ++addr) {
        Wire.beginTransmission(addr);
        uint8_t err = Wire.endTransmission();

        if (err == 0) {
            ++found;
            Serial.print(F("0x"));
            if (addr < 0x10) Serial.print('0');
            Serial.print(addr, HEX);
            Serial.print(F("  "));
            if (addr < 100) Serial.print(' ');
            if (addr < 10) Serial.print(' ');
            Serial.print(addr);
            Serial.print(F("   "));
            Serial.println(lookupKnownDevice(addr));
        } else if (err == 4) {
            Serial.print(F("0x"));
            if (addr < 0x10) Serial.print('0');
            Serial.print(addr, HEX);
            Serial.println(F(": error de bus"));
        }
    }

    Serial.print(F("Total: "));
    Serial.print(found);
    Serial.println(F(" dispositivo(s)"));
    if (found == 0) {
        Serial.println(F("Revisa cableado y pull-ups (4.7k a 3.3V)."));
    }
    Serial.print(F("> "));
}

void setup() {
    Serial.begin(115200);
    delay(200);
    Wire.begin(I2C_SDA_PIN, I2C_SCL_PIN);
    Wire.setClock(I2C_CLOCK_HZ);
    printHelp();
}

void loop() {
    if (!Serial.available()) return;

    int c = Serial.read();
    if (c < 0) return;
    if (c == '\r' || c == '\n' || c == ' ' || c == '\t') return;

    switch (c) {
        case 's':
        case 'S':
            scanI2C();
            break;
        case 'h':
        case 'H':
        case '?':
            printHelp();
            break;
        default:
            Serial.print(F("comando desconocido '"));
            Serial.print((char)c);
            Serial.println(F("', pulsa h"));
            Serial.print(F("> "));
            break;
    }
}
