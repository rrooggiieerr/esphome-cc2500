# Texas Instruments CC2500 Low-Power 2.4 GHz RF Transceiver component for ESPHome.

[![GitHub Release][releases-shield]][releases]
[![Licence][license-shield]][license]
[![Maintainer][maintainer-shield]][maintainer]  
[![GitHub Sponsors][github-shield]][github]
[![PayPal][paypal-shield]][paypal]
[![BuyMeCoffee][buymecoffee-shield]][buymecoffee]
[![Patreon][patreon-shield]][patreon]

## Introduction

This [ESPHome External Component](https://esphome.io/components/external_components) allows you to
transmit and receive data using a compatible CC2500 transceiver. Other components that depend on
the CC2500 can build upon it.

This component itself doesn't let you send data nor interpret the received data, you need a
separate component that implements the required data format for your hardware. When debug or
verbose logging is enabled, it logs all incoming traffic on the default channel with default
settings.

The CC2500’s built-in temperature sensor is currently implemented in a basic way for ESP8266-based
boards when GDO0 is connected to A0.

## Hardware required

- ESP8266, ESP32 or another ESPHome supported microcontroller
- CC2500 transceiver module

## Wiring

The solder pads on the CC2500 transceiver are slightly closer together than the width of a ribbon
cable, so soldering requires a steady hand.

<img src="wiring1.jpg" width="33%"/><img src="wiring2.jpg" width="33%"/><img src="wiring3.jpg" width="33%"/>

If you prefer, I’ve created a Wemos Mini Shield that has been tested with both the D1 mini and the
C3 mini. Contact me if you’d like to purchase one!

<img src="Wemos CC2500 Shield A.jpg" width="33%"/>

|     CC2500       | NodeMcu V3 |Wemos D1 mini<br/>Shield V1|Wemos D1 mini<br/>Shield V2|Wemos C3 mini<br/>Shield V1|Wemos C3 mini<br/>Shield V2|
|:----------------:|:----------:|:-------------:|:-------------:|:-------------:|:-------------:|
|       GND        |     G      |      GND      |      GND      |      GND      |      GND      |
|       VDD        |     3V     |      3V3      |      3V3      |      3V3      |      3V3      |
|       SI         | D7/GPIO13  |     GPIO13    |     GPIO13    |     GPIO4     |     GPIO4     |
|      SCLK        | D5/GPIO14  |     GPIO14    |     GPIO14    |     GPIO2     |     GPIO2     |
|       SO         | D6/GPIO12  |     GPIO12    |     GPIO12    |     GPIO3     |     GPIO3     |
| GDO2 (interrupt) | D1/GPIO5   |     GPIO5     |     GPIO15    |     GPIO10    |     GPIO5     |
|GDO0 (temperature)|     A0     |       NC      |       A0      |       NC      |     GPIO0     |
|       CSn        | D8/GPIO15  |     GPIO15    |     GPIO16    |     GPIO5     |     GPIO1     |

## Configuration variables

- __cs_pin__ (Required): The pin to use for the SPI chip select.
- __gdo0_pin__ (Optional): The ESP pin connected to the CC2500 GDO0 pin. Required to read the
  CC2500 temperature.
- __gdo2_pin__ (Optional): The ESP pin connected to the CC2500 GDO2 pin. Required for receiving
  data.
- __output_power__ (Optional): The transmission power for outgoing signals.

### ESPHome example configuration

To set up this CC2500 component, first define a top-level SPI component specifying which pins to use.

Example YAML for Wemos C3 mini and CC2500 Shield:

```
esphome:
  name: cc2500

external_components:
  - source:
      type: git
      url: https://github.com/rrooggiieerr/esphome-cc2500
      # ref: 0.0.3
    components: [cc2500]

esp32:
  board: lolin_c3_mini
  variant: esp32c3

# Enable logging
logger:
  level: DEBUG

# Enable Home Assistant API
api:
  encryption:
    key: ...

ota:
  - platform: esphome
    password: ...

wifi:
  ssid: !secret wifi_ssid
  password: !secret wifi_password
```

CC2500 settings for Wemos D1 mini and CC2500 Shield V1.0

```
spi:
  clk_pin: GPIO14
  mosi_pin: GPIO13
  miso_pin: GPIO12

cc2500:
  cs_pin: GPIO15
  gdo2_pin: GPIO5 # Interrupt
  output_power: 0xFF
```

CC2500 settings for Wemos D1 mini and CC2500 Shield V2.0

```
spi:
  clk_pin: GPIO14
  mosi_pin: GPIO13
  miso_pin: GPIO12

cc2500:
  cs_pin: GPIO16
  gdo0_pin: A0
  gdo2_pin: GPIO15 # Interrupt
  output_power: 0xFF

sensor:
  - platform: cc2500
    temperature:
      name: "Temperature"
      update_interval: 5s
```

SPI settings for Wemos C3 mini and CC2500 Shield V1.0

```
spi:
  clk_pin: GPIO2
  mosi_pin: GPIO4
  miso_pin: GPIO3

cc2500:
  cs_pin: GPIO5
  gdo2_pin: GPIO10 # Interrupt
  output_power: 0xFF
```

SPI settings for Wemos C3 mini and CC2500 Shield V2.0

```
spi:
  clk_pin: GPIO2
  mosi_pin: GPIO4
  miso_pin: GPIO3

cc2500:
  cs_pin: GPIO1
  gdo0_pin: GPIO0
  gdo2_pin: GPIO5 # Interrupt
  output_power: 0xFF
```

## Documentation:

[Texas Instruments CC2500 datasheet](https://www.ti.com/lit/ds/symlink/cc2500.pdf)

## Credits:

[Tor Røttum](https://github.com/torrottum)'s
[ESPHome IKEA Ansluta component](https://github.com/torrottum/ikea-ansluta-esphome) was very
helpful for making this component.

## Contribution and appreciation

You can contribute to this component, or show your appreciation, in the following ways.

### Star this external component

Help other ESPHome and CC2500 users find this external component by starring this GitHub page.
Click **⭐ Star** on the top right of the GitHub page.

### Support my work

Do you enjoy using this ESPHome component? Please consider supporting my work through one of the
following platforms, your donation is greatly appreciated and keeps me motivated:

[![GitHub Sponsors][github-shield]][github]
[![PayPal][paypal-shield]][paypal]
[![BuyMeCoffee][buymecoffee-shield]][buymecoffee]
[![Patreon][patreon-shield]][patreon]

### ESPHome support

[Book a one-hour ESPHome support session](https://buymeacoffee.com/rrooggiieerr/e/470127). I’ll
help you troubleshoot your ESPHome setup or answer your ESPHome-related questions.

What can be done in one hour:
- ESPHome walktrough, I explain to you how ESPHome works
- Assistance setting up your ESP device
- Install and configure an ESPHome (External) Component

What takes more time:
- Support for ESPHome Component developers

### Hire me

If you would like to have an ESPHome component developed for your product or are in need for a
freelance ESP developer for your project please contact me, you can find my email address on
[my GitHub profile](https://github.com/rrooggiieerr).

[releases]: https://github.com/rrooggiieerr/esphome-cc2500/releases
[releases-shield]: https://img.shields.io/github/v/release/rrooggiieerr/esphome-cc2500?style=for-the-badge
[license]: ./LICENSE
[license-shield]: https://img.shields.io/github/license/rrooggiieerr/esphome-cc2500?style=for-the-badge
[maintainer]: https://github.com/rrooggiieerr
[maintainer-shield]: https://img.shields.io/badge/MAINTAINER-%40rrooggiieerr-41BDF5?style=for-the-badge
[paypal]: https://paypal.me/seekingtheedge
[paypal-shield]: https://img.shields.io/badge/PayPal-00457C?style=for-the-badge&logo=paypal&logoColor=white
[buymecoffee]: https://www.buymeacoffee.com/rrooggiieerr
[buymecoffee-shield]: https://img.shields.io/badge/Buy%20Me%20a%20Coffee-ffdd00?style=for-the-badge&logo=buy-me-a-coffee&logoColor=black
[github]: https://github.com/sponsors/rrooggiieerr
[github-shield]: https://img.shields.io/badge/sponsor-30363D?style=for-the-badge&logo=GitHub-Sponsors&logoColor=ea4aaa
[patreon]: https://www.patreon.com/seekingtheedge/creators
[patreon-shield]: https://img.shields.io/badge/Patreon-F96854?style=for-the-badge&logo=patreon&logoColor=white