#!/bin/bash

# File to store the current state
toggle_file="/tmp/polybar_date_toggle"

# Get the day of the month
day=$(date +"%-d")

# Determine the correct suffix
if [[ $day =~ ^(11|12|13)$ ]]; then
    suffix="th"
else
    case $((day % 10)) in
        1) suffix="st" ;;
        2) suffix="nd" ;;
        3) suffix="rd" ;;
        *) suffix="th" ;;
    esac
fi

# If the toggle file doesn't exist, create it and set to 0 (default mode)
if [ ! -f "$toggle_file" ]; then
    echo "0" > "$toggle_file"
fi

# Read the current state
state=$(cat "$toggle_file")

# Toggle the state between 0 (default) and 1 (alt)
if [ "$1" == "toggle" ]; then
    if [ "$state" -eq "0" ]; then
        echo "1" > "$toggle_file"
    else
        echo "0" > "$toggle_file"
    fi
fi

# Display date based on current state
if [ "$state" -eq "0" ]; then
    # Default date format
    echo "$(date +"%I:%M %p")"
else
    # Alternate date format with suffix
    echo "$(date +"%a, (%-m)%b/")$day$suffix$(date +"/%Y, %I:%M:%S %p")"
fi
