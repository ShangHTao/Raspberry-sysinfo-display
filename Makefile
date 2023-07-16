TARGET=oled_i2c_show_status
#此处用于定义编译器，编译的时候可以使用
# make CC=aarch64-none-linux-gcc，来定义交叉编译用的编译器
CC=gcc
SRC=$(wildcard src/*.c)
INC=./inc
#此处用于定义搜索wiringPi.h头文件的位置
EXT_INC=../WiringPi/wiringPi
#此处用于定义引用的libwiringPi.so
LIB=wiringPi
#此处用于搜索libwiringPi.so的位置
LDFLAGS=-L../WiringPi/wiringPi
#把src变量里所有后缀为*.c的文件替换成*.o
OBJ=$(patsubst %.c,%.o,$(SRC))
CFLAGS=-I$(INC) -I$(EXT_INC)

all:$(TARGET)
$(TARGET):$(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS) -l$(LIB)
%.o:%.c
	$(CC) -o $@ -c $< $(CFLAGS)

.PHONY:clean
ifeq ($(OS),Windows_NT)
RM=cmd /c del
FixPath=$(subst /,\,$1)
else
RM=rm -f
FixPath=$1
endif
clean:
	$(RM) $(call FixPath,./src/*.o)