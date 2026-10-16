#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/time.h>

#include <ncurses.h>

#include "connectivity.h"
#include "logger.h"
int internet_status = 0;
void connectivity_init(void)
{
    int sock;
    int status;
    struct sockaddr_in server;
    struct timeval tv;

    mvprintw(11,42,"Internet");
    mvprintw(11,58,":");

    sock = socket(AF_INET, SOCK_STREAM, 0);

    if(sock < 0)
    {
        attron(COLOR_PAIR(3) | A_BOLD);
        mvprintw(11,60,"DISCONNECTED");
        attroff(COLOR_PAIR(3) | A_BOLD);

        write_log("Socket Creation Failed");
        return;
    }

    /* 1 second timeout */
    tv.tv_sec = 1;
    tv.tv_usec = 0;

    setsockopt(sock, SOL_SOCKET, SO_SNDTIMEO, &tv, sizeof(tv));
    setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));

    memset(&server, 0, sizeof(server));

    server.sin_family = AF_INET;
    server.sin_port = htons(53);

    inet_pton(AF_INET, "8.8.8.8", &server.sin_addr);

    status = connect(sock, (struct sockaddr *)&server, sizeof(server));

    if(status == 0)
    {
internet_status = 1;
        attron(COLOR_PAIR(2) | A_BOLD);
        mvprintw(11,60,"CONNECTED");
        attroff(COLOR_PAIR(2) | A_BOLD);

        write_log("Internet Connected");
    }
    else
    {
internet_status = 0;
        attron(COLOR_PAIR(3) | A_BOLD);
        mvprintw(11,60,"DISCONNECTED");
        attroff(COLOR_PAIR(3) | A_BOLD);

        write_log("Internet Disconnected");
    }

    close(sock);
}
