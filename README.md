# Moral-o-Smart
> it's a smart Moral-o-mat by using ESP32-C3 based MCU and e-paper displays instead of paper.

## board
As MCU we are using the inexpensive ESP32-C3 based board called "LuatOS CORE ESP32".

On aliexpress for around 2,30 EUR (serial chip for debugging) or around 1,70 EUR (without debugging). 

LuatOS CORE ESP32 (ESP32-C3): https://de.aliexpress.com/item/1005006292473768.html

### pinout
![pinout](docs/luatos_CORE-ESP32_pinout.webp)

### platformio board settings
Currently there is no board variation in the espressivf32 arduino code.

Just use `board = airm2m_core_esp32c3` in your platformio.ini. It has a similar pinout for SPI/I2C, builtin LEDs and buttons.

For more details: [platformio.ini](platformio.ini)

## e-paper displays
To have a compact but readable version, we are using the 2.13" black/white version with SPI interface.

On aliexpress for around 7 EUR each: https://de.aliexpress.com/item/1005004644515880.html

## touch buttons
To toggle the 3 displays, we just use the inexpensive touch button modules (TTP223).

On aliexpress for around 0,10 EUR each: https://de.aliexpress.com/item/32964219843.html

## libraries
- [zinggjm/GxEPD2](https://registry.platformio.org/libraries/zinggjm/GxEPD2) (drive the e-paper displays)
- [lennarthennigs/Button2](https://registry.platformio.org/libraries/lennarthennigs/Button2) (for the touch buttons)

## ToDo
- [ ] build class for the displays
- [ ] build class for configuration
- [ ] build class for deep-sleep handling
- [ ] add deep-sleep
- [ ] wake up MCU from deep-sleep (by all 4 buttons)
  - [ ] touch button 1: toggle display 1
  - [ ] touch button 2: toggle display 2
  - [ ] touch button 3: toggle display 3
  - [ ] button 4: activate WiFi configuration AP
- [ ] add [AsyncWebserver](https://registry.platformio.org/libraries/me-no-dev/ESP%20Async%20WebServer)

