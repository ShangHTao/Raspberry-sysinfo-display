```
oled_show
├─ CMakeLists.txt
├─ Makefile
├─ README.md
├─ inc
│  ├─ character.h
│  ├─ ssd1306.h
│  ├─ sys_status.h
│  └─ vpopen.h
├─ obj
│  ├─ .gitkeep
└─ src
   ├─ main.c
   ├─ ssd1306.c
   ├─ sys_status.c
   └─ vpopen.c
```

# How to compile 

## use cmake
	$mkdir build
	$cd build
	$cmake ../
	$make
	
## use make
you can export CC=xxx-gnu-gcc to support cross compile at host pc,but need to cross compile libwiringPi first

	$make # just one line, if you in rpi 3b or 4b ,you have to install gcc toolchin first
	
## in rpi openwrt you need to install procps-ng procps-ng-ps
	$opkg install procps-ng procps-ng-ps
	
## auto check oled_i2c_show_status app status by cron table(使用cron计划任务来定时检测程序的运行状态)

```bash
#!/bin/sh
#save this shell script as oledctl.sh to /etc/cron.d/oledctl.sh
#Check the oled_i2c_show_status app status
if [ $(ps -ef | grep -c "oled_i2c_show_status") -lt 2 ]; then
        echo "0.96 oled display start now";
        /usr/bin/oled_i2c_show_status &
else
        echo "0.96 oled display app is running";
fi
```

将下面的内容，导入到cron任务列表中
解释为，每30分钟，执行一下程序，用于检测oled_i2c_show_status程序是否在运行，再根据情况来执行操作
```
*/30 * * * * /etc/cron.d/oledctl.sh
```
