#!/bin/sh

SCRIPT_DIR=$(dirname "$0")
LED_CONTROLLER_PATH=$(readlink -f "$SCRIPT_DIR/../led_controller/led_controller.c")

WIFI_SSID=$(printenv WIFI_SSID)
WIFI_PASSWORD=$(printenv WIFI_PASSWORD)

if [ -z "$WIFI_SSID" ] || [ -z "$WIFI_PASSWORD" ]; then
    echo "Warning: Both WIFI_SSID and WIFI_PASSWORD must be provided as arguments."
fi

git stash push -m "Pre-build stash"

if [ ! -z "$WIFI_SSID" ] && [ ! -z "$WIFI_PASSWORD" ]; then
    sed -i "s|wifi_ssid|${WIFI_SSID}|g" $LED_CONTROLLER_PATH
    sed -i "s|wifi_password|${WIFI_PASSWORD}|g" $LED_CONTROLLER_PATH
fi
