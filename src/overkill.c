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

void overkill(char ** cmd, int noc)
{
    int i=0;
    while(i<32768)
    {
        if(bg_pr[bg_iter[i]])
            kill(bg_iter[i], 9);
        i++;
    }
}