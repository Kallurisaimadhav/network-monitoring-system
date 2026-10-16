#include <stdio.h>
#include <string.h>
#include <ncurses.h>

#include "traffic.h"
#include "config.h"
#include "connectivity.h"

void traffic_init(void)
{
    FILE *fp;

    char line[256];
    char iface[32];

    unsigned long rx;
    unsigned long tx;

    static unsigned long prev_rx = 0;
    static unsigned long prev_tx = 0;

    double rx_kbps = 0.0;
    double tx_kbps = 0.0;

    fp = fopen("/proc/net/dev","r");

    if(fp == NULL)
        return;

    /* Skip header lines */
    fgets(line,sizeof(line),fp);
    fgets(line,sizeof(line),fp);

    while(fgets(line,sizeof(line),fp))
    {
        if(sscanf(line,
                  " %31[^:]: %lu %*u %*u %*u %*u %*u %*u %*u %lu",
                  iface,
                  &rx,
                  &tx) == 3)
        {
            if(strcmp(iface,"lo") == 0)
                continue;

            if(internet_status)
            {
                rx_kbps = (rx - prev_rx) / 1024.0 / refresh_time;
                tx_kbps = (tx - prev_tx) / 1024.0 / refresh_time;
            }
            else
            {
                rx_kbps = 0.0;
                tx_kbps = 0.0;
            }

            prev_rx = rx;
            prev_tx = tx;

            attron(COLOR_PAIR(2) | A_BOLD);
            mvprintw(14,42,"RX Speed :");
            mvprintw(15,42,"TX Speed :");
            attroff(COLOR_PAIR(2) | A_BOLD);

            mvprintw(14,55,"%8.2f KB/s", rx_kbps);
            mvprintw(15,55,"%8.2f KB/s", tx_kbps);

            break;
        }
    }

    fclose(fp);
}
