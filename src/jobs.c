#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<pwd.h>
#include<unistd.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<signal.h>
#include<grp.h>
#include<time.h>
#include<sys/wait.h>
#include<fcntl.h>
#include<termios.h>
#include<sys/utsname.h>
#include<stdbool.h>
#include<errno.h>
#include<dirent.h>
#include "../gvar.h"

void jobs(char ** cmd, int noc)
{
    char p_id[10009], p_name[10009], stat[10009];
    int i=0;
    while(i<32768)
    {
        // printf("Jobs reach loop\n");
        if (bg_pr[bg_iter[i]])
        {
            // printf("Jobs reach\n");
            char path[1024];
            strcpy(path, "/proc/");
            char cur_pr[10009];
            sprintf(cur_pr, "%d", bg_iter[i]);
            // variable to get the path of the stat of the process we 
            // need to find out here
            strcat(path, cur_pr);
            strcat(path, "/stat");
            FILE *fp = fopen(path, "r");
            // Since status is the third parameter that it returns 
            // we have to extract ID and name of process
            fscanf(fp, "%s %s %s", p_id, p_name, stat);
            char stat_print[10009];
            if(strcmp(stat,"R")==0 || strcmp(stat,"S")==0)
                strcpy(stat_print,"Running");
            else
                strcpy(stat_print,"Stopped");
            printf("[%d] %s %s [%d]", i+1, stat_print, bg_pr[bg_iter[i]], bg_iter[i]);
            printf("\n");
        }
        i++;
    }
}