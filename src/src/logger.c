#include <stdio.h>
#include <time.h>
#include <errno.h>
#include <string.h>
#include "logger.h"

void logger_init(void)
{
    FILE *fp;

fp = fopen("/tmp/network.log", "a");
     if(fp == NULL)
   {
    printf("Log File Error\n");
    printf("errno = %d\n", errno);
    printf("Reason = %s\n", strerror(errno));
    return;
   }

    fprintf(fp, "========== Application Started ==========\n");

    fclose(fp);

    printf("Logger Initialized\n");
}

void write_log(char message[])
{
    FILE *fp;
    time_t t;

    fp = fopen("/tmp/network.log", "a");
    if(fp == NULL)
        return;

    t = time(NULL);

    fprintf(fp, "%s : %s\n",ctime(&t), message);

    fclose(fp);
}
