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

void fg_bg(char ** cmd, int noc)
{
    pid_t pid, wpid, stat;
    pid = get_id(atoi(cmd[1]));
    if(pid<0)
    {
        printf("%s does not exist\n", cmd[1]);
        return;
    }
    printf("%d\n", pid);
    free(bg_pr[pid]);
    bg_pr[pid] = NULL;
    do
    {
        wpid = waitpid(pid, &stat, 0);
    }
    while(!(WIFEXITED(stat) || WIFSIGNALED(stat)));
}