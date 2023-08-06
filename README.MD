# วิธีใช้งาน
- เปิดสวิตช์อุปกรณ์
- ใส่กำบังในจุดอ่าน หันด้านตัดมุมให้ตรง
- ใส่หลอดด้าย หันด้านบาร์โค๊ดให้ตรงกับลูกศร

# เงื่อนไขการทำงาน
|  ตรวจจับ | ผล | จักร |  Alarm  |
|  -----------  |  ---------
|  หลอดด้ายและกำบัง    |  ตรงกัน    |  ON  |  OFF  |
|  หลอดด้ายและกำบัง    |  ไม่ตรงกัน  |  OFF  |  ON  |
|  ไม่มีหลอดด้าย        |           |  OFF  |  OFF  |
|  ไม่มีกำบัง             |           |  OFF  |	OFF  |
|  มีหลอดด้าย ไม่มีกำบัง  |		OFF	|  OFF  |
|  มีกำบัง ไม่มีหลอดด้าย  |	  OFF  |	OFF  |

# TTGO T-Display

## Quick start
https://github.com/Xinyuan-LilyGO/TTGO-T-Display/tree/master
https://s2ins.com/product/barcode-scanner-1d-2d-qr-code-module-mh-ttlusb/

## Pinout
| Name       | V18    |
| ---------- | ------ |
| TFT Driver | ST7789 |
| TFT_MISO   | N/A    |
| TFT_MOSI   | 19     |
| TFT_SCLK   | 18     |
| TFT_CS     | 5      |
| TFT_DC     | 16     |
| TFT_RST    | 23     |
| TFT_BL     | 4      |
| I2C_SDA    | 21     |
| I2C_SCL    | 22     |
| ADC_IN     | 34     |
| BUTTON1    | 35     |
| BUTTON2    | 0      |
| ADC Power  | 14     |

## Hardware Specifications:
- Chipset: ESPRESSIF-ESP32 240MHz Xtensa® single-/dual-core 32-bit LX6 microprocessor
- FLASH Memory: QSPI flash 4MB
- SRAM: 520 KB SRAM
- Button: Reset
- USB to TTL IC: CP2104
- Modular interface: UART, SPI, SDIO, I2C, LED PWM, TV PWM, I2S, IRGPIO, ADC, capacitor touch sensor, DACLNA  pre-amplifier
- Display: IPS ST7789V 1.14 Inch
- Interface: SPI
- LCD type: IPS
- Controller: ST7789
- Resolution: 135(H)BGR x 240(V)
- Working Voltage: 2.7V-4.2V
- Working Current: About 60MA
- Sleep Current: about 120uA
- Working temperature range: -40℃ ~ +85℃
- Size&Weight: 51.52 x 25.04 x 8.54mm(7.81g)

## Power Supply Specifications:
- Power Supply: USB 5V/1A
- Charging current: 500mA
- Battery: 3.7V lithium battery (Not included)
- JST Connector: 2Pin 1.25mm
- USB: Type-C

## Wi-Fi:
- Standard: FCC/CE-RED/IC/TELEC/KCC/SRRC/NCC
- Protocol: 802.11 b/g/n(802.11n，speed up to150Mbps)A-MPDU and A-MSDU polymerization，support 0.4μS Protection interval
- Frequency range: 2.4GHz~2.5GHz(2400M~2483.5M)
- Transmit Power: 22dBm
- Communication distance: 300m

## Bluetooth:
- Protocol: Meet Bluetooth v4.2BR/EDR and BLE standard
- Radio frequency: With -97dBm sensitivity NZIF receiver Class-1,Class-2&Class-3 emitter AFH
- Audio frequency: CVSD&SBC audio frequency

## Software specification:
- Wi-Fi Mode: Station/SoftAP/SoftAP+Station/P2P
- Security mechanism: WPA/WPA2/WPA2-Enterprise/WPS
- Encryption Type: AES/RSA/ECC/SHA
- Firmware upgrade: UART download/OTA（Through network/host to download and write firmware）
- Software Development: Support cloud server development /SDK for user firmware development
- Networking protocol: IPv4、IPv6、SSL、TCP/UDP/HTTP/FTP/MQTT
- User Configuration: AT + Instruction set, cloud server, android/iOSapp
- OS: FreeRTOS
