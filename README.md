# esphome-cc2500
Texas Instrumants CC2500 Low-Power 2.4 GHz RF Transceiver external component for ESPHome.

## Hardware required
- ESP8266 or ESP32
- CC2500 transceiver

## Wiring ##

|CC2500| ESP8266 |
|:----:|:-------:|
| GND  |    G    |
| VDD  |   3V    |
|  SI  |D7/GPIO13|
| SCLK |D5/GPIO14|
|  SO  |D6/GPIO12|
| GD02 |         |
| GDO0 |         |
| CSn  |D8/GPIO15|

![](wiring1.jpg)
![](wiring2.jpg)
![](wiring3.jpg)
## ESPHome exaple code
```
esphome:
  name: cc2500

external_components:
  - source: github://rrooggiieerr/esphome-livingcolors1

esp8266:
  board: nodemcu

# Enable logging
logger:
  level: DEBUG

spi:
  clk_pin: GPIO14
  mosi_pin: GPIO13
  miso_pin: GPIO12

cc2500:
  cs_pin: GPIO15
  channel_number: 3
  output_power: 0xFF

```

## Documentation
[Texas Instrumants CC2500 datasheet](https://www.ti.com/lit/ds/symlink/cc2500.pdf)

## Credits
[Torrotum's IKEA Ansluta ESPHome external component](https://github.com/torrottum/ikea-ansluta-esphome) was very helpful form making this component.
