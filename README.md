# I2C_scanner

Escáner I2C bajo demanda para ESP32 (DevKit v1), basado en PlatformIO +
framework Arduino. Lista las direcciones de 7 bits que responden ACK en
el bus y, cuando coincide con un dispositivo conocido, muestra su
nombre.

## Hardware

- ESP32 DevKit v1 (`board = esp32dev`)
- I2C: **SDA = GPIO21**, **SCL = GPIO22**
- Pull-ups externas de **4.7 kΩ a 3.3 V** en SDA y SCL
- Velocidad: 100 kHz

## Compilar y subir

Requiere [PlatformIO Core](https://platformio.org/install/cli) o la
extensión de VSCode.

```bash
pio run                  # compila
pio run -t upload        # flashea
pio device monitor -b 115200
```

## Uso

Al abrir el monitor serial verás:

```text
I2C Scanner (ESP32)
  SDA=21 SCL=22 @ 100 kHz
Comandos:
  s : escanear bus I2C
  h : ayuda
>
```

Comandos:

| Tecla     | Acción                        |
|-----------|-------------------------------|
| `s`       | Escanea el rango `0x03..0x77` |
| `h` o `?` | Muestra la ayuda              |

Ejemplo de salida con un OLED SSD1306 y un BME280 conectados:

```text
Escaneando 0x03..0x77 ...
HEX   DEC   Dispositivo
----  ----  ------------------
0x3C   60   SSD1306 OLED
0x76  118   BME280 / BMP280
Total: 2 dispositivo(s)
>
```

## Personalizar pines o velocidad

Edita `platformio.ini` y cambia los `build_flags`:

```ini
build_flags =
    -D I2C_SDA_PIN=21
    -D I2C_SCL_PIN=22
    -D I2C_CLOCK_HZ=100000
```

## Recuperación de bus colgado

Si todas las direcciones devuelven `error de bus`, lo más probable es
que SDA esté en bajo. Apaga el ESP32, desconecta el dispositivo
sospechoso y vuelve a probar. La recuperación automática (toggling de
SCL) no está implementada en esta versión.

## Diseño

Ver [docs/superpowers/specs/2026-05-13-i2c-scanner-design.md](docs/superpowers/specs/2026-05-13-i2c-scanner-design.md).
