#!/bin/sh

SCRIPT_DIR=$(dirname "$0")
LED_CONTROLLER_PATH=$(readlink -f "$SCRIPT_DIR/../led_controller/led_controller.c")

if [ -f "$LED_CONTROLLER_PATH" ]; then
    sed -i "s|${WIFI_SSID}|wifi_ssid|g" $LED_CONTROLLER_PATH
    sed -i "s|${WIFI_PASSWORD}|wifi_password|g" $LED_CONTROLLER_PATH
else
    echo "Error: led_controller.c not found at $LED_CONTROLLER_PATH"
fi
