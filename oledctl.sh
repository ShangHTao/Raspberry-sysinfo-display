#!/bin/sh
#Check the oled_i2c_show_status app status
if [ $(ps -ef | grep -c "oled_i2c_show_status") -lt 2 ]; then
        echo "0.96 oled display start now";
        /usr/bin/oled_i2c_show_status &
else
        echo "0.96 oled display app is running";
fi
