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

void function_cd(char ** cmd)
{
    char rop[1024];
	// cd ~ and cd <NULL>
	if (cmd[1] == NULL || strcmp(cmd[1],"~") == 0)
		chdir(Home);
	// Looks for the directory from home
	else if(cmd[1][0] == '~')
    {
		strcpy(rop, present+end+1);
		chdir(Home);
		if(chdir(cmd[1]+2) == -1)
        {
			printf(" HMMS: %s: No such file or directory\n", cmd[1]);
			chdir(rop);
		}
	}
	else{
		if (chdir(cmd[1]) == -1) {
			printf(" HMMS: %s: No such file or directory\n", cmd[1]);
		}
	}
}