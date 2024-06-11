#!/bin/sh

WIFI_SSID=$1
WIFI_PASSWORD=$2

if [ -z "$WIFI_SSID" ] || [ -z "$WIFI_PASSWORD" ]; then
    echo "Warning: Both WIFI_SSID and WIFI_PASSWORD must be provided as arguments."
fi

git stash push -m "Pre-build stash"

if [ ! -z "$WIFI_SSID" ] && [ ! -z "$WIFI_PASSWORD" ]; then
    sed -i "s/wifi_ssid/${WIFI_SSID}/g" led_controller.c
    sed -i "s/wifi_password/${WIFI_PASSWORD}/g" led_controller.c
fi
