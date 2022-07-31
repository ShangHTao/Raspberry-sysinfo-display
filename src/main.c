#include <stdio.h>
#include <string.h>
#include "ssd1306.h"
#include "sys_status.h"

int main(void)
{
    int fd_oled;
    char buff[200];//缓冲区
/***********************************下面开始显示操作*******************************/
    OLED_Init(&fd_oled);
 	OLED_Refresh(fd_oled);
    while(1)
    {
        memset(buff,0x00,sizeof(buff));
        getIp(buff);
        OLED_ShowString(3,2,showtime(),12);

        OLED_ShowString(3,18,"IP:",12);
        OLED_ShowString(21,18,buff,12);

        memset(buff,0x00,sizeof(buff));
        sprintf(buff,"CPU LOAD:%.0f%% %d`C",get_sysCpuUsage(),getCPUtemperature()/1000);
        OLED_ShowString(3,32,buff,12);

        memset(buff,0x00,sizeof(buff));
        sprintf(buff,"RAM:%d / %d MB ",(getRAM_total()-getRAM_free())/1024,getRAM_total()/1024);
		OLED_ShowString(3,46,buff,12);

        OLED_DrawLine(0,0,127,0);
        OLED_DrawLine(0,0,0,63);
        OLED_DrawLine(0,63,127,63);
        OLED_DrawLine(127,0,127,63);
        OLED_DrawLine(0,16,127,16);
        OLED_DrawLine(0,15,127,15);
        OLED_Refresh(fd_oled);
        OLED_Clear(fd_oled);
       // sleep(1);
    }
}


