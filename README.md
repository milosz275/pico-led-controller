# Raspberry Pi Pico W LED Controller with Web interface

[![Build](https://github.com/mldxo/pico-led-controller/actions/workflows/cmake.yml/badge.svg)](https://github.com/mldxo/pico-led-controller/actions/workflows/cmake.yml)
[![CodeQL](https://github.com/mldxo/pico-led-controller/actions/workflows/codeql.yml/badge.svg)](https://github.com/mldxo/pico-led-controller/actions/workflows/codeql.yml)

This project is a simple example of how to manage a WS2812B LED strip with a Raspberry Pi Pico W and a Web interface.

## Prerequisites

Packages

```bash
sudo apt-get update
sudo apt-get install -y cmake gcc-arm-none-eabi libnewlib-arm-none-eabi build-essential
```

Environmental variables

```bash
export PICO_SDK_PATH="insert_path_here"
export PICO_EXTRAS_PATH="insert_path_here"
export PICO_EXAMPLES_PATH="insert_path_here"
export FREERTOS_KERNEL_PATH="insert_path_here"
export PICO_BOARD="pico_w"
```

`led_controller/wifi_credentials.h`

```c
#ifndef _WIFI_CREDENTIALS_H
#define _WIFI_CREDENTIALS_H

#define WIFI_SSID "wifi_ssid"
#define WIFI_PASSWORD "wifi_password"

#endif
```

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## References

- [pico-sdk](https://github.com/raspberrypi/pico-sdk)
- [pico-examples](https://github.com/raspberrypi/pico-examples)
- [makefsdata.py](https://github.com/krzmaz/pico-w-webserver-example/pull/1/files/4b3e78351dd236f213da9bebbb20df690d470476#diff-e675c4a367e382db6f9ba61833a58c62029d8c71c3156a9f238b612b69de279d)
