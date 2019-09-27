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

int child_stat;

void lol()
{
	printf("Process exited\n");
}

void bg_exe(char **cmd, int noc)
{
    // bg_pgm will be 1 if it is bg
	bg_pgm = 0;
	if (cmd[1]==NULL)
		bg_pgm = 0;
	else if (*cmd[noc-1] == '&')
	{
		cmd[noc-1] = '\0';
		bg_pgm = 1;
	}
	
	pid_t ret_fork_1 = fork();
    // fork() returns 0 when child is in control, negative on failing 
    //and positive on returning to parent process
	cmd[noc] = '\0';
	if (ret_fork_1 < 0)
	{
		printf("HMMS: ERROR: Couldn't fork\n");
		exit(1);
	}
    // execvp() returns -1 when the execution fails
	else if (!ret_fork_1)
	{
		if(execvp(*cmd, cmd) < 0)
		printf("Invalid command\n");
		// if (bg_pgm)
		// {
			// printf("Background reach\n");
			bg_pr[ret_fork_1] = malloc(1024);
			bg_len++;
            bg_iter[bg_len] = ret_fork_1;
			strcpy(bg_pr[ret_fork_1], cmd[0]);
			printf("[%d]\n",ret_fork_1);
			signal(SIGTSTP, SIG_IGN);
			// printf("%s: (%d) exited successfully\n", cmd[0], ret_fork_1);
		// }
		// else 
		// {
		// 	// signal(SIGTSTP, SIG_IGN);
		// 	waitpid(ret_fork_1, &child_stat, 0);
		// 	printf("%s: (%d) exited successfully\n", cmd[0], ret_fork_1);
		// }
		exit(0);
	}
	else if (ret_fork_1 > 0)
	{
		// bg_pr[ret_fork_1] = malloc(1024);
		// bg_len++;
        // bg_iter[bg_len] = ret_fork_1;
		// strcpy(bg_pr[ret_fork_1], cmd[0]);
		if (bg_pgm)
		{
			// printf("Background reach\n");
			bg_pr[ret_fork_1] = malloc(1024);
			bg_len++;
            bg_iter[bg_len] = ret_fork_1;
			strcpy(bg_pr[ret_fork_1], cmd[0]);
			printf("[%d]\n",ret_fork_1);
			// printf("%s: (%d) exited successfully\n", cmd[0], ret_fork_1);
			signal(SIGCHLD,lol);
		}
		else
		{
			// signal(SIGTSTP, SIG_IGN);
			// process_now = ret_fork_1;
			// tcsetpgrp(0,pid);
			waitpid(ret_fork_1, &child_stat, WUNTRACED);
			// printf("%s: (%d) exited successfully\n", cmd[0], ret_fork_1);
		}
	}
}