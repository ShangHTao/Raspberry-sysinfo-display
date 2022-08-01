#!/bin/sh
while :
do
    if [ $(ps -ef | grep -c "oled_i2c_show_status") -lt 2 ]; then
    $( /home/pi/Desktop/oled_show/oled_i2c_show_status  &) ; 
    else 
	    #echo "is running"; 
    fi
    sleep 60
done
