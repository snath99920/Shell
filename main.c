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
#include "gvar.h"

int main()
{
	clear;
	process_now = getpid();
	// set home
    getcwd(Home, sizeof(Home));
	end = strlen(Home);
	signal(SIGINT, nothing);
	signal(SIGTSTP, sigint_handler);
	hist_count = 0;
	while(true)
    {
        displayShell(end, Home);
		// signal(SIGTSTP, sigint_handler);
		int sc = 0, t = 0, cmd_sc[10001], noc = 1;
		// sets the final point as \n here
		memset(line, '\n', 1000001);
		fgets(line, 1000001, stdin);
        // strtok returns NULL when there is no token left to retrieve
		cmd[0] = strtok(line," \n\t");
        if(cmd[0] == NULL)
			continue;
		while((cmd[noc] = strtok(NULL, " \n\t")) != NULL)
        {
			// seperating of commands using a ';' is implemented
			// here. Note that I tried my best but you have to seperate
			// the functions and the semicolon using a space.
			// For example "pwd ; echo Chimichangas"
			if(*cmd[noc] == ';')
            {
				sc = noc;
				cmd_sc[t++] = noc;
			}
			noc++;
		}
		if(sc != noc-1)
			cmd_sc[t++] = noc;

		int pCom[1024];
		int it = 0;
		int pl = 0, pr = 0;
		int in = 0, out1 = 0;
		int fd_out, fd_in;
		int i = 0;

		if(!sc)
		{
			int k = 0;
			while(k<noc)
			{
				if(strcmp(cmd[k],"|")==0)
					pCom[it++]=k;
				k++;
			}
			pCom[it++]=noc;
			if(it!=1)
			{
				fd_in = dup(STDIN_FILENO);
				fd_out = dup(STDOUT_FILENO);
				int k = 0, left = 0, z = -1;
				while(k<it)
				{
					int right = pCom[k];
					z = piped_exec(&cmd[left],z,it-1-k,left,right);
					left = right+1;
					k++;
				}
				dup2(fd_in, STDIN_FILENO);
				close(fd_in);
			}
			else
				redirect(cmd, noc);
		}
			
		else
		{
			int left = 0, right;
			int i = 0;
			while(i<t)
			{
				it=0;
				right=cmd_sc[i];
				int iter = left;
				while(iter<right)
				{
					if(strcmp(cmd[iter],"|")==0)
						pCom[it++]=iter;
					iter++;
				}
				pCom[it++]=right-left;
				if(it==1)
					redirect(&cmd[left],right-left);
				else
				{
					fd_in = dup(STDIN_FILENO);
					fd_out = dup(STDOUT_FILENO);
					int g=left, z=-1;
					int iter = 0;
					while(iter<it)
					{
						int h = pCom[iter];
						z = piped_exec(&cmd[g],z,it-1-iter,g,h);
						g = h+1;
						iter++;
					}
					dup2(fd_in, STDIN_FILENO);
					close(fd_in);		
				}
				left = right+1;
				i++;
			}
		}
				//redirect(cmd, noc);
			//run_shell(cmd, noc);
		// else
        // {
		// 	int l = 0, r, i = 0;
		// 	while(i<t)
        //     {
		// 		r=cmd_sc[i];
		// 		run_shell(&(cmd[l]), r-l);
		// 		l=r+1;
        //         i++;
		// 	}
		// }
		// Only 20 history 
		hist_count++;
		hist_count = hist_count%20;
	}
	return 0;
}