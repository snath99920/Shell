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

void kjob(char ** cmd, int noc)
{
    pid_t pid;
    pid = get_id(atoi(cmd[1]));
    if(pid < 0)
    {
        printf("%s does not exist\n", cmd[1]);
        return;
    }
    if(bg_pr[pid] != NULL)
    {
        if(noc == 3)
            kill(pid, atoi(cmd[2]));
        else
        {
            perror("Error\n");
            return;
        }
    }
}