#!/bin/sh

SCRIPT_DIR=$(dirname "$0")
LED_CONTROLLER_PATH=$(readlink -f "$SCRIPT_DIR/../led_controller/led_controller.c")

if [ -f "$LED_CONTROLLER_PATH" ]; then
    if [ $(git stash list | wc -l) -gt 0 ]; then
        git checkout stash@{0} -- "$LED_CONTROLLER_PATH"
    else
        echo "No stashes available to apply."
    fi
else
    echo "Error: led_controller.c not found at $LED_CONTROLLER_PATH"
fi
