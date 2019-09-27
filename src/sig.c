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

void signalHandler(int sig, siginfo_t *si, void *context)
{
	int status;
	int pid, pos;
	int i;

	switch(sig)	
	{
		case SIGQUIT:
		exit(0);
		break;

		case SIGTERM:
		pid = waitpid(-1, NULL, WNOHANG);
		if(pid>0)
			kill(pid , SIGTERM);
		break;
		
		case SIGCHLD:
		pid = waitpid(-1, NULL, WNOHANG);
		if(pid>0)
		{
			
			kill(pid , SIGTERM);
			if(arr[pid][0]!=0)
			{
				fprintf(stderr, "\n%s with pid %d exited!\n" ,arr[pid], pid);
				for(i=0;joblist[i].pid!=-1;i++)
				{
					if(joblist[i].pid == pid)
						pos = i;
				}
				for(i=pos;joblist[i+1].pid!=-1;i++)
				{
					joblist[i]=joblist[i+1];
				}
				joblist[i].pid = -1;

			}
			arr[pid][0]=0;
		}
		break;
	}
}

void ctrlC(int signo)
{
	if(signo == SIGINT)
	{
		if(getpid() != shellpid)
			kill(getpid(),9);
		else
		{
			printf("\n");
		}
	}
}

void ctrlZ(int signo)
{
	if(signo == SIGTSTP)
	{
		printf("Detected Ctrl+Z\n");
	}

}