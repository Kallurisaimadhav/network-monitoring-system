#include <stdio.h>
#include <sys/statvfs.h>
#include <ncurses.h>

#include "disk.h"
float disk_usage = 0.0;
float disk_init(void)
{
    struct statvfs disk;

    unsigned long total;
    unsigned long free_space;
    unsigned long used;

    float usage = 0.0;

    if(statvfs("/", &disk) != 0)
        return 0;

    total = disk.f_blocks * disk.f_frsize;
    free_space = disk.f_bavail * disk.f_frsize;
    used = total - free_space;

    if(total != 0)
        usage = ((float)used / total) * 100.0;
disk_usage = usage;
    attron(COLOR_PAIR(2) | A_BOLD);
    mvprintw(14,2,"Disk Usage   :");
    attroff(COLOR_PAIR(2) | A_BOLD);

    mvprintw(14,18,"%6.2f %%", usage);

    mvprintw(15,2,"Total Disk   : %.2f GB",
             total / (1024.0 * 1024.0 * 1024.0));

    mvprintw(16,2,"Used Disk    : %.2f GB",
             used / (1024.0 * 1024.0 * 1024.0));

    mvprintw(17,2,"Free Disk    : %.2f GB",
             free_space / (1024.0 * 1024.0 * 1024.0));

    return usage;
}
