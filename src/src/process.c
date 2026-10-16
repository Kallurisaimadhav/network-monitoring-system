#include <stdio.h>
#include <dirent.h>
#include <ctype.h>
#include <string.h>
#include <ncurses.h>

#include "process.h"

void process_init(void)
{
    DIR *dir;
    struct dirent *entry;
    FILE *fp;

    char path[100];
    char command[100];

    int row = 19;
    int count = 0;

    dir = opendir("/proc");

    if(dir == NULL)
        return;

    attron(COLOR_PAIR(4) | A_BOLD);
    mvprintw(18,2,"TOP PROCESSES");
    attroff(COLOR_PAIR(4) | A_BOLD);

    mvhline(19,2,'-',30);

    attron(COLOR_PAIR(4) | A_BOLD);
    mvprintw(20,2,"PID");
    mvprintw(20,12,"COMMAND");
    attroff(COLOR_PAIR(4) | A_BOLD);

    row = 21;

    while((entry = readdir(dir)) != NULL)
    {
        if(!isdigit(entry->d_name[0]))
            continue;

        sprintf(path,"/proc/%s/comm",entry->d_name);

        fp = fopen(path,"r");

        if(fp == NULL)
            continue;

        if(fgets(command,sizeof(command),fp) == NULL)
        {
            fclose(fp);
            continue;
        }

        fclose(fp);

        command[strcspn(command,"\n")] = 0;

        /* Skip noisy kernel worker threads */
        if(strncmp(command,"kworker",7)==0)
            continue;

        if(strncmp(command,"migration",9)==0)
            continue;

        if(strncmp(command,"cpuhp",5)==0)
            continue;

        attron(COLOR_PAIR(2));
mvprintw(row,2,"%-6s",entry->d_name);
attroff(COLOR_PAIR(2));

attron(COLOR_PAIR(1));
mvprintw(row,12,"%-20s",command);
attroff(COLOR_PAIR(1));
        row++;
        count++;

        if(count >= 2)
            break;
    }

    closedir(dir);
}

