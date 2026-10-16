#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <ifaddrs.h>
#include <arpa/inet.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <ncurses.h>

#include "interface.h"

void interface_init(void)
{
    struct ifaddrs *ifaddr;
    struct ifaddrs *ifa;

    int fd;
    struct ifreq ifr;

    char ip[32] = "N/A";
    char mac[32] = "N/A";

    if(getifaddrs(&ifaddr) == -1)
        return;

    attron(COLOR_PAIR(2) | A_BOLD);
    mvprintw(7,42,"Interface :");
    attroff(COLOR_PAIR(2) | A_BOLD);

    for(ifa = ifaddr; ifa != NULL; ifa = ifa->ifa_next)
    {
        if(ifa->ifa_addr == NULL)
            continue;

        if(strcmp(ifa->ifa_name, "lo") == 0)
            continue;

        if(ifa->ifa_addr->sa_family == AF_INET)
        {
            inet_ntop(AF_INET,
                      &((struct sockaddr_in *)ifa->ifa_addr)->sin_addr,
                      ip,
                      sizeof(ip));

            fd = socket(AF_INET, SOCK_DGRAM, 0);

            if(fd >= 0)
            {
                memset(&ifr, 0, sizeof(ifr));
                strncpy(ifr.ifr_name, ifa->ifa_name, IFNAMSIZ - 1);

                if(ioctl(fd, SIOCGIFHWADDR, &ifr) == 0)
                {
                    sprintf(mac,
                            "%02X:%02X:%02X:%02X:%02X:%02X",
                            (unsigned char)ifr.ifr_hwaddr.sa_data[0],
                            (unsigned char)ifr.ifr_hwaddr.sa_data[1],
                            (unsigned char)ifr.ifr_hwaddr.sa_data[2],
                            (unsigned char)ifr.ifr_hwaddr.sa_data[3],
                            (unsigned char)ifr.ifr_hwaddr.sa_data[4],
                            (unsigned char)ifr.ifr_hwaddr.sa_data[5]);
                }

                close(fd);
            }

            mvprintw(7,56,"%s", ifa->ifa_name);
            mvprintw(8,42,"IP Address : %s", ip);
            mvprintw(9,42,"MAC Addr   : %s", mac);

            if(ifa->ifa_flags & IFF_UP)
                mvprintw(10,42,"Status     : UP");
            else
                mvprintw(10,42,"Status     : DOWN");

            break;
        }
    }

    freeifaddrs(ifaddr);
}
