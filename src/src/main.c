#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <ncurses.h>

#include "cpu.h"
#include "memory.h"
#include "disk.h"
#include "interface.h"
#include "connectivity.h"
#include "traffic.h"
#include "process.h"
#include "config.h"
#include "alerts.h"
int main(void)
{
    time_t now;
    struct tm *tm_info;
    char datetime[100];

    initscr();
    noecho();
    curs_set(0);

    start_color();
    use_default_colors();

    init_pair(1, COLOR_CYAN,   -1);
    init_pair(2, COLOR_GREEN,  -1);
    init_pair(3, COLOR_RED,    -1);
    init_pair(4, COLOR_YELLOW, -1);

    while(1)
    {
        erase();

        now = time(NULL);
          /* Convert UTC to IST */
    now += (5 * 3600) + (30 * 60);

    tm_info = gmtime(&now);
        
        strftime(datetime, sizeof(datetime),
                 "%a %b %d %H:%M:%S %Y", tm_info);

        /* Title */
        attron(COLOR_PAIR(1) | A_BOLD);
        mvprintw(0,15,"EMBEDDED NETWORK MONITORING SYSTEM");
        attroff(COLOR_PAIR(1) | A_BOLD);

        mvhline(1,0,'=',78);

        /* Date and Refresh */
        attron(COLOR_PAIR(2));
        mvprintw(2,2,"Date : %s", datetime);
        mvprintw(2,50,"Refresh : %d s", refresh_time);
        attroff(COLOR_PAIR(2));

        mvhline(3,0,'=',78);

        /* Section Headings */
        attron(COLOR_PAIR(4) | A_BOLD);
        mvprintw(4,2,"SYSTEM STATUS");
        mvprintw(4,42,"NETWORK STATUS");
        attroff(COLOR_PAIR(4) | A_BOLD);

        /* Vertical Separator */
        mvvline(5,39,ACS_VLINE,17);

        /* Dashboard Modules */
        cpu_init();
        memory_init();
        disk_init();
        interface_init();
        connectivity_init();
        traffic_init();
        process_init();
/* ===================== STATUS BAR ===================== */



attron(COLOR_PAIR(4) | A_BOLD);
mvprintw(23,2,"STATUS :");
attroff(COLOR_PAIR(4) | A_BOLD);

/* Move cursor after "STATUS :" */
move(23,11);

if(internet_status == 0)
{
    attron(COLOR_PAIR(3) | A_BOLD);
    printw(" INTERNET DISCONNECTED ");
    attroff(COLOR_PAIR(3) | A_BOLD);
}

if(cpu_usage >= 80.0)
{
    attron(COLOR_PAIR(3) | A_BOLD);
    printw("| HIGH CPU ");
    attroff(COLOR_PAIR(3) | A_BOLD);
}

if(memory_usage >= 80.0)
{
    attron(COLOR_PAIR(3) | A_BOLD);
    printw("| HIGH MEMORY ");
    attroff(COLOR_PAIR(3) | A_BOLD);
}

if(disk_usage >= 90.0)
{
    attron(COLOR_PAIR(3) | A_BOLD);
    printw("| LOW DISK ");
    attroff(COLOR_PAIR(3) | A_BOLD);
}

if(internet_status &&
   cpu_usage < 80.0 &&
   memory_usage < 80.0 &&
   disk_usage < 90.0)
{
    attron(COLOR_PAIR(2) | A_BOLD);
    printw(" SYSTEM HEALTHY ");
    attroff(COLOR_PAIR(2) | A_BOLD);
}



        refresh();

        sleep(refresh_time);
    }

    endwin();

    return 0;
}
