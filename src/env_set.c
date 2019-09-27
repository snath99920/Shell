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

void set_env(char ** cmd, int noc)
{
    char *flag = NULL;
    flag = getenv(cmd[1]);
    int res;
    if(flag == NULL)
        res = setenv(cmd[1], cmd[2], 0);
    else
        res = setenv(cmd[1], cmd[2], 1);
    if(res == -1)
    {
        perror("Error\n");
        return;
    }
}