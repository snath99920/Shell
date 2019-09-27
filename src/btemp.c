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
	if (ret_fork_1 < 0)
	{
		printf("HMMS: ERROR: Couldn't fork\n");
		exit(1);
	}
    // execvp() returns -1 when the execution fails
	else if (ret_fork_1 == 0)
	{
		// The control moves into the following if it is a background
		// program. Here is makes a grandchild who executes the process
		// and the child waits for the grandshild to end
		if (bg_pgm)
		{
			pid_t ret_fork_2 = fork();
			if (ret_fork_2 == 0)
			{
				int flag = execvp(*cmd, cmd);
				if (flag == -1) 
					printf("HMMS: ERROR: Command not found\n");
			}
			waitpid(ret_fork_1, &child_stat, 0);
			printf("%s: (%d) exited successfully\n", cmd[0], ret_fork_1);
		}
		// Here the program runs on the foreground and it is just basic
		// execution
		else
		{
			int flag = execvp(*cmd, cmd);
			if (flag == -1)
				printf("HMMS: ERROR: Command not found\n");
		}
		
		//printf("%s: (%d) exited successfully\n", cmd[0], ret_fork_2);
	}
	else if (ret_fork_1 > 0)
	{
		if (bg_pgm)
            printf("[%d]\n",ret_fork_1);
		else
			waitpid(ret_fork_1, &child_stat, 0);
	}
}