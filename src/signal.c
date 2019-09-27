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

void nothing(int s)
{
//     pid_t pid = getpid();
//     if (pid != process_now)
//         kill(process_now, 9);
}

void sigint_handler(int s)
{
//     if(s == SIGTSTP)
//     {
        // pid_t pid = getpid();
        // bg_pr[pid] = malloc(1024);
        // bg_len++;
        // bg_iter[bg_len] = pid;
        // signal(pid, 20);
        // strcpy(bg_pr[pid], cmd[0]);
        
//         printf("[%d]\n", pid);
//         kill(pid, SIGTSTP);
//     }
//     else
//     {
//         signal(s, SIG_DFL);
//         raise(s);
//     }
}