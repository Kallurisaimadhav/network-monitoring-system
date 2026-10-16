#include <stdio.h>
#include <string.h>
#include <ncurses.h>

#include "memory.h"
float memory_usage = 0.0;
float memory_init(void)
{
    FILE *fp;

    char label[50];

    unsigned long total = 0;
    unsigned long available = 0;
    unsigned long used = 0;

    float usage = 0.0;

    fp = fopen("/proc/meminfo","r");

    if(fp == NULL)
        return 0;

    while(fscanf(fp,"%49s",label) != EOF)
    {
        if(strcmp(label,"MemTotal:") == 0)
        {
            fscanf(fp,"%lu",&total);
        }
        else if(strcmp(label,"MemAvailable:") == 0)
        {
            fscanf(fp,"%lu",&available);
        }
        else
        {
            fscanf(fp,"%*[^\n]\n");
        }
    }

    fclose(fp);

    used = total - available;

    if(total != 0)
        usage = ((float)used / total) * 100.0;
         memory_usage = usage;
    attron(COLOR_PAIR(2) | A_BOLD);
    mvprintw(8,2,"Memory Usage :");
    attroff(COLOR_PAIR(2) | A_BOLD);

    mvprintw(8,18,"%6.2f %%",usage);

    mvprintw(10,2,"Total Memory : %.2f MB", total / 1024.0);
    mvprintw(11,2,"Used Memory  : %.2f MB", used / 1024.0);
    mvprintw(12,2,"Free Memory  : %.2f MB", available / 1024.0);

    return usage;
}

