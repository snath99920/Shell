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


void redirect(char ** cmd, int noc)
{
	int fd0=-1, fd=-1;
	char input[64], output[64], tp[3];
	int in=0, out=0;
	int in_num=2048, out_num=2048;
	int s_redir=0;
	while(s_redir<noc)
	{
		if(strcmp(cmd[s_redir], "<")==0)
		{        
		    cmd[s_redir]=NULL;
		    strcpy(input,cmd[s_redir+1]);
		    if(!in)
		    {
		       	in=1;
		       	in_num=s_redir;
		    }           
		}               

		else if((strcmp(cmd[s_redir],">")==0) || (strcmp(cmd[s_redir],">>")==0))
		{   
		  	strcpy(tp,cmd[s_redir]);   
		    cmd[s_redir]=NULL;
		    strcpy(output,cmd[s_redir+1]);
		    if(!out)
            {
		       	out=1;
		       	out_num=s_redir;
		    }
		}      
        s_redir++;   
	}
	if(!in && !out)
    {
		run_shell(cmd,noc);
		return;
	}
	if(in && out)
    {
		fd0 = open(input, O_RDONLY, 0);
		if (fd0 < 0) 
        {
       		perror(input);
       		return;
    	}
    	if(strcmp(tp,">")==0)
	   		fd = open(output, O_CREAT|O_TRUNC|O_WRONLY, 0644);
			if (fd < 0) 
            { 
				perror(output);
			    return; 
			}
		    else
			fd = open(output, O_CREAT|O_WRONLY|O_APPEND, 0644);
			    if (fd < 0) 
                { 
				    perror(output);
				    return; 
			    }

    	dup2(fd0,0);
    	close(fd0);
		dup2(fd,1);
		close(fd);
    	run_shell(cmd, min(in_num,out_num));
		int fd_in = dup(STDIN_FILENO);	
		int fd_out = dup(STDOUT_FILENO);
		dup2(fd_in, STDIN_FILENO);
		dup2(fd_out, STDOUT_FILENO);
		close(fd_in);
		close(fd_out);
		return;
	}
	if(in)
    {
		fd0 = open(input, O_RDONLY, 0);
		if (fd0 < 0) 
        {
       		perror(input);
       		return;
    	}
        dup2(fd0,0);
        close(fd0);
        run_shell(cmd, min(in_num,out_num));
		int fd_in = dup(STDIN_FILENO);
		dup2(fd_in, STDIN_FILENO);
		close(fd_in);
		return;
	}
	if(out)
    {
		if(strcmp(tp,">")==0)
		{
	   		fd = open(output, O_CREAT|O_TRUNC|O_WRONLY, 0644);
			if (fd < 0) 
            { 
				perror(output);
				return;
			} 
		}
		if(strcmp(tp,">>")==0)
        {
			fd = open(output, O_CREAT|O_WRONLY|O_APPEND, 0644);
			if (fd < 0) 
            { 
				perror(output);
				return; 
			}
		}
		dup2(fd,1);
		close(fd);
		run_shell(cmd,min(in_num,out_num));
		int fd_out = dup(STDOUT_FILENO);
		dup2(fd_out, STDOUT_FILENO);
		close(fd_out);
		return;
	}
}