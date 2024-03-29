#include "sys_status.h"
void getIp(char ip_addr[])
{
    int sockfd;
    struct ifconf ifconf;
    struct ifreq *ifreq;
    char buf[512];//缓冲区
    char time[20];
    ifconf.ifc_len =512;//初始化ifconf
    ifconf.ifc_buf = buf;

    if ((sockfd =socket(AF_INET,SOCK_DGRAM,0))<0)
    {
        perror("socket" );
        exit(1);
    }
    ioctl(sockfd, SIOCGIFCONF, &ifconf); //获取所有接口信息
    //接下来一个一个的获取IP地址
    ifreq = (struct ifreq*)ifconf.ifc_buf;
    // printf("ifconf.ifc_len:%d\n",ifconf.ifc_len);
    // printf("sizeof (struct ifreq):%d\n",sizeof (struct ifreq));
    for (int i=(ifconf.ifc_len/sizeof (struct ifreq)); i>0; i--)
    {
        if(ifreq->ifr_flags == AF_INET){ //for ipv4
            //printf("name =[%s]\n" , ifreq->ifr_name);
            //printf("local addr = [%s]\n" ,inet_ntoa(((struct sockaddr_in*)&(ifreq->ifr_addr))->sin_addr));
            if(strcmp(ifreq->ifr_name,"wlan0")==0)//是否与wlan0相同
            {
                strcpy(ip_addr,inet_ntoa(((struct sockaddr_in*)&(ifreq->ifr_addr))->sin_addr));
            } else if(strcmp(ifreq->ifr_name,"br-lan")==0)//是否与br-lan相同,此修改用于树莓派3b
            {
                strcpy(ip_addr,inet_ntoa(((struct sockaddr_in*)&(ifreq->ifr_addr))->sin_addr));
            }
                       
            ifreq++;
        }
    }
}

char* showtime(void)//当前时间
{
    time_t rawtime;
    struct tm *info;
    static char buffer[80];
   time( &rawtime );
   info = localtime( &rawtime );
   strftime(buffer, 80, "PI %F %H:%M\0", info);
   //printf("格式化的日期 & 时间 : |%s|\n", buffer );
   return buffer;
}

int getCPUtemperature(void)
{
    int fd;
    int re=0,i;
    char buff[10];
    fd = open ("/sys/class/thermal/thermal_zone0/temp", O_RDONLY);
    if(fd < 0)
    {
            perror("open:/sys/class/thermal/thermal_zone0/temp error");
            exit (0);
    }
    i=read(fd,buff,10);
    if(i<0)
    {
            perror("read:/sys/class/thermal/thermal_zone0/temp error");
            exit (0);
    }
    re = atoi(buff);
    close(fd);
    //printf("re=%d size=%d\n",re,i);
   return re;
}
mem_info_t getRAM(void)
{
    mem_info_t mem;
    int fd,i;
    char buff[83];
    char kb[3];

    fd = open ("/proc/meminfo", O_RDONLY);
    if(fd < 0)
    {
            perror("open:/proc/meminfo error");
            exit (0);
    }
    i=read(fd,buff,83);
    if(i<0)
    {
            perror("read:/proc/meminfo error");
            exit (0);
    }
    //printf("%s i=%d\n",buff,i);
    sscanf(buff,"%s %u %s %s %u",mem.MemTotal,&mem.total,kb,mem.MemFree,&mem.free);
    //printf("tot=%u free=%u \n",mem.total,mem.free);
    close(fd);
    return mem;
}

double cal_cpuoccupy (cpu_occupy_t *o, cpu_occupy_t *n)
{
    double od, nd;
    double id, sd;
    double cpu_use ;
 
    od = (double) (o->user + o->nice + o->system +o->idle+o->softirq+o->iowait+o->irq);//第一次(用户+优先级+系统+空闲)的时间再赋给od
    nd = (double) (n->user + n->nice + n->system +n->idle+n->softirq+n->iowait+n->irq);//第二次(用户+优先级+系统+空闲)的时间再赋给od
 
    id = (double) (n->idle);    //用户第一次和第二次的时间之差再赋给id
    sd = (double) (o->idle) ;    //系统第一次和第二次的时间之差再赋给sd
    if((nd-od) != 0)
        cpu_use =100.0 - ((id-sd))/(nd-od)*100.00; //((用户+系统)乖100)除(第一次和第二次的时间差)再赋给g_cpu_used
    else 
        cpu_use = 0;
    return cpu_use;
}
 
void get_cpuoccupy (cpu_occupy_t *cpust)
{
    int fd;
    int n,i;
    char buff[256];
    cpu_occupy_t *cpu_occupy;
    cpu_occupy=cpust;

    fd = open ("/proc/stat", O_RDONLY);
    if(fd < 0)
    {
            perror("open:/proc/stat error");
            exit (0);
    }
    i=read(fd,buff,256);
    if(i<0)
    {
            perror("read:/proc/stat error");
            exit (0);
    }
    //printf("%s i=%d\n",buff,i);
    sscanf (buff, "%s %u %u %u %u %u %u %u", cpu_occupy->name, &cpu_occupy->user, &cpu_occupy->nice,&cpu_occupy->system, &cpu_occupy->idle ,&cpu_occupy->iowait,&cpu_occupy->irq,&cpu_occupy->softirq);
    close(fd);
}
 
double get_sysCpuUsage()
{
    cpu_occupy_t cpu_stat1;
    cpu_occupy_t cpu_stat2;
    double cpu;
    get_cpuoccupy((cpu_occupy_t *)&cpu_stat1);
    sleep(1);
    //第二次获取cpu使用情况
    get_cpuoccupy((cpu_occupy_t *)&cpu_stat2);
 
    //计算cpu使用率
    cpu = cal_cpuoccupy ((cpu_occupy_t *)&cpu_stat1, (cpu_occupy_t *)&cpu_stat2);
 
    return cpu;
}
