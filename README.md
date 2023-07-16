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