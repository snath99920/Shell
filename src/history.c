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
#include<errno.h>
#include<dirent.h>
#include "../gvar.h"

void print_hist()
{
    int i = 0;
    while(i<20)
    {
        if (history[i]) 
            printf("%4d  %s\n", i+1, history[i]);
        i++;
    }
}