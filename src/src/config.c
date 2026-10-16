#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "config.h"

int refresh_time = 2;

int cpu_alert = 80;
int memory_alert = 85;
int disk_alert = 90;
void config_init(void)
{
    FILE *fp;
    char line[100];

    fp = fopen("/etc/network_monitor.conf", "r");

    if(fp == NULL)
    {
        printf("Using Default Configuration\n");
        return;
    }

    while(fgets(line, sizeof(line), fp))
    {
        if(strncmp(line, "REFRESH_TIME=",13)==0)
        {
            refresh_time = atoi(line + 13);
        }
        else if(strncmp(line,"CPU_ALERT=",10)==0)
{
    cpu_alert = atoi(line+10);
}
else if(strncmp(line,"MEMORY_ALERT=",13)==0)
{
    memory_alert = atoi(line+13);
}
else if(strncmp(line,"DISK_ALERT=",11)==0)
{
    disk_alert = atoi(line+11);
}
    }

      printf("CPU Alert     = %d%%\n", cpu_alert);
printf("Memory Alert  = %d%%\n", memory_alert);
printf("Disk Alert    = %d%%\n", disk_alert);
    fclose(fp);

    printf("Refresh Time = %d seconds\n", refresh_time);
}
