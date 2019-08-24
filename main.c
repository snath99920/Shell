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
		if(!sc)
			run_shell(cmd, noc);
		else
        {
			int l = 0, r, i = 0;
			while(i<t)
            {
				r=cmd_sc[i];
				run_shell(&(cmd[l]), r-l);
				l=r+1;
                i++;
			}
		}
		// Only 20 history 
		hist_count++;
		hist_count = hist_count%20;
	}
	return 0;
}