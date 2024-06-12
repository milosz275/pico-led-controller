# Raspberry Pi Pico W LED Controller with Web interface

[![Build](https://github.com/mldxo/pico-led-controller/actions/workflows/cmake.yml/badge.svg)](https://github.com/mldxo/pico-led-controller/actions/workflows/cmake.yml)
[![CodeQL](https://github.com/mldxo/pico-led-controller/actions/workflows/codeql.yml/badge.svg)](https://github.com/mldxo/pico-led-controller/actions/workflows/codeql.yml)

This project is a simple example of how to manage a WS2812B LED strip with a Raspberry Pi Pico W and a Web interface.

## Prerequisites

```bash
export PICO_SDK_PATH="insert_path_here"
export PICO_EXTRAS_PATH="insert_path_here"
export PICO_EXAMPLES_PATH="insert_path_here"
export FREERTOS_KERNEL_PATH="insert_path_here"
export PICO_BOARD="pico_w"
```

## Remarks

Directories [pico_w](pico_w) and [ws2812](ws2812) are imported from [pico-examples](https://github.com/raspberrypi/pico-examples) repository.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
