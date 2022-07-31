#ifndef __SYS_STATUS_H
#define __SYS_STATUS_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <fcntl.h>
#include "vpopen.h"
typedef struct cpu_occupy_          //定义一个cpu occupy的结构体
{
    char name[20];                  //定义一个char类型的数组名name有20个元素
    unsigned int user;              //定义一个无符号的int类型的user
    unsigned int nice;              //定义一个无符号的int类型的nice
    unsigned int system;            //定义一个无符号的int类型的system
    unsigned int idle;              //定义一个无符号的int类型的idle
    unsigned int iowait;
    unsigned int irq;
    unsigned int softirq;
}cpu_occupy_t;

void getIp(char ip_addr[]);
char *showtime(void);
int getCPUtemperature(void);
int getRAM_total(void);
int getRAM_available(void);
int getRAM_free(void);

double cal_cpuoccupy (cpu_occupy_t *o, cpu_occupy_t *n);
void get_cpuoccupy (cpu_occupy_t *cpust);
double get_sysCpuUsage(void);
#endif