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

void run_shell(char ** cmd,int noc)
{
	// hist_count = 0;
	if(strcmp(cmd[0],"pwd")==0)
	{
        PrintWorkingDirectory();
		history[0] = "pwd";
	}
    else if(strcmp(cmd[0],"echo")==0)
	{
		echo(cmd, noc);
		char buf[100] = "echo ";
		history[hist_count] = strcat(buf,cmd[1]);
	}
    else if(strcmp(cmd[0],"cd")==0)
	{
		function_cd(cmd);
		char buf[100] = "cd ";
		history[hist_count] = strcat(buf, cmd[1]);
	}
	else if(strcmp(cmd[0],"pinfo")==0)
	{
		pinfo(cmd);
		history[hist_count] = "pinfo";
	}
	else if(strcmp(cmd[0],"ls")==0)
    {
		history[hist_count] = "ls";
		int x = 0;
        int i = 1, stat;
		while(i<noc)
        {
			if(cmd[i][0]!=45)
            {
                // return values of chdir is 0 for success 
                // and -1 for failure
				if (*cmd[i] == '\0' || *cmd[i] == '~')
					chdir(Home);
				else if(cmd[i][0] == '~')
                {
					char dir[1024];
					strcpy(dir, present+end+1);
					chdir(Home);
                    stat = chdir(cmd[i]+2);
					if(stat == -1)
                    {
						printf(" HMMS: %s: No such file or directory\n", cmd[i]);
						chdir(dir);
					}
				}
				else
                {
                    stat = chdir(cmd[i]);
					if (stat == -1) 
						printf(" HMMS: %s: No such file or directory\n", cmd[i]);
				}
                x = i;
				break;
			}
            i++;
		}
		if(x)
        {
            int j = x;
			while(j<noc-1)
            {
				strcpy(cmd[j], cmd[j+1]);
                j++;
            }
			cmd[noc-1] = '\0';
			list(cmd, noc-1);
			chdir(present);
		}
		else
			list(cmd, noc);
	}
	else if(strcmp(cmd[0],"history")==0)
	{
		print_hist();
	}
    else if(strcmp(cmd[0],"exit")==0)
    {
		printf(" HMMS: Goodbye!\n");
        exit(0);
    }
	else
	{
		history[hist_count] = cmd[0];
		bg_exe(cmd, noc);
	}
}