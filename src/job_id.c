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

int get_id(int pid)
{
    int i=0, j=0;
    while(i<32767 && j != pid)
    {
        //if(bg_pr[bg_iter[i]] != NULL)
        j++;
        i++;
    }
    if(i==32767)
        return -1;
    return bg_iter[i-1];
}