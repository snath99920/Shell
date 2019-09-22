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
	// set home
    getcwd(Home, sizeof(Home));
	end = strlen(Home);
	hist_count = 0;
	while(true)
    {
        int pCom[1024];
		int fdout, fdin;
		int i, pl = 0, pr = 0;
		displayShell(end, Home);
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
		int in = 0, out1 = 0;
		int dec = 0;
		if(!sc)
        {
			int ch_bar=0;
			// Check for piping in the command entered
			while(ch_bar<noc)
			{
				if(strcmp(cmd[ch_bar],"|")==0)
					pCom[dec++]=ch_bar;
				ch_bar++;
			}		
			pCom[dec++]=noc;
			if(dec!=1)
			{
				fdin = dup(STDIN_FILENO);
				fdout = dup(STDOUT_FILENO);
				int left=0;
				int exe=-1;
				int j=0;
				while(j<dec)
				{
					int right=pCom[j];
					exe=piped_exec(&cmd[left], exe, dec-1-j, left, right);
					left=right+1;
					j++;
				}
				dup2(fdin, STDIN_FILENO);
				close(fdin);
			}
			else
				redirect(cmd,noc);
        }
        else
        {
			int left=0,right,i=0;
			while(i<t)
            {
				dec=0;
				right=cmd_sc[i];
				int ch_bar = left;
				while(ch_bar<right)
				{
					if(strcmp(cmd[ch_bar],"|")==0)
						pCom[dec++]=ch_bar;
					ch_bar++;
				}
				pCom[dec++]=right-left;
				if(dec==1)
					redirect(&cmd[left],right-left);
				else
                {
					int cmd_l=left,exe=-1;
					fdin = dup(STDIN_FILENO);
					fdout = dup(STDOUT_FILENO);
					for(int j=0; j<dec; j++)
                    {
						int cmd_r=pCom[j];
						exe=piped_exec(&cmd[g], exe, dec-1-j, cmd_l, cmd_r);
						cmd_l=cmd_r+1;
					}
					dup2(fdin, STDIN_FILENO);
					close(fdin);		
				}
				left=right+1;
                i++;
			}
		}
		// Only 20 history 
		hist_count++;
		hist_count = hist_count%20;
	}
	return 0;
}