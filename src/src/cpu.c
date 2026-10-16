#include <stdio.h>
#include <ncurses.h>

#include "cpu.h"
float cpu_usage = 0.0;
void cpu_init(void)
{
    FILE *fp;

    char cpu[10];

    unsigned long user, nice, system, idle;

    static unsigned long prev_user = 0;
    static unsigned long prev_nice = 0;
    static unsigned long prev_system = 0;
    static unsigned long prev_idle = 0;

    unsigned long total;
    unsigned long prev_total;
    unsigned long diff_total;
    unsigned long diff_idle;

    float usage = 0.0;

    fp = fopen("/proc/stat", "r");

    if(fp == NULL)
        return ;

    if(fscanf(fp,"%s %lu %lu %lu %lu",
              cpu,
              &user,
              &nice,
              &system,
              &idle) != 5)
    {
        fclose(fp);
        return ;
    }

    fclose(fp);

    total = user + nice + system + idle;
    prev_total = prev_user + prev_nice + prev_system + prev_idle;

    diff_total = total - prev_total;
    diff_idle  = idle - prev_idle;

    if(diff_total != 0)
        usage = 100.0 * (diff_total - diff_idle) / diff_total;
       cpu_usage = usage;
    prev_user = user;
    prev_nice = nice;
    prev_system = system;
    prev_idle = idle;

    attron(COLOR_PAIR(2) | A_BOLD);
    mvprintw(7,2,"CPU Usage    :");
    attroff(COLOR_PAIR(2) | A_BOLD);
     mvprintw(7,18,":");
    mvprintw(7,20,"%6.2f %%", usage);

    return ;
}
