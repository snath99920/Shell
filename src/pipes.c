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

int piped_exec(char ** cmd, int input_pipe, int fl, int left, int right) 
{
	int fd_pipe[2];
    int input_fd = -1, output_fd = -1;
    // pipe() command returns a -1 on failure
	if(fl != 0)
    	if(pipe(fd_pipe) == -1)
            perror("Unable to create pipes");
    if(input_pipe >= 0) 
        input_fd = input_pipe;
    if(fl != 0)
    	output_fd = fd_pipe[1];
    pid_t pid = fork();
    pid_t wpid;
    // fork() command returns a negative value on failing, a positive
    // value when the control returns to the parent process and 
    // a value of 0 when child is running
    if(pid < 0)
        perror("Error forking!");
	else if(pid==0)
    {
		if(input_fd >= 0) 
        {
            dup2(input_fd, STDIN_FILENO);
            close(input_fd);
        }
        if(output_fd >= 0) 
        {
            dup2(output_fd, STDOUT_FILENO);
            close(output_fd);
		}	
		redirect(cmd, right-left);
		exit(0);
	}
    else 
    {
        if(input_fd >= 0) 
            close(input_fd);
		if(output_fd >= 0) 
            close(output_fd);
		wait(NULL);
	}
	return fd_pipe[0];
}