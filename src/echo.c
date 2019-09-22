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

void echo(char ** cmd, int numC)
{
    for(int i=1; i<numC; i++)
    {
        int fl=0;
        if(cmd[i][0]==34 || cmd[i][0]==92)
            fl=1;
        if(cmd[i][strlen(cmd[i])-1]==34 && strlen(cmd[i])!=2)
        {
            if(cmd[i][strlen(cmd[i])-2]==92)
                cmd[i][strlen(cmd[i])-2]=34;
            cmd[i][strlen(cmd[i])-1]=32;
        }
        printf("%s ",cmd[i]+fl);
    }
    printf("\n");
}