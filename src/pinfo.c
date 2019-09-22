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
#define bsize 1024

void pinfo(char ** cmd)
{
	char find_proc[bsize], pid[100], p_name[100], status[100];
	int file_in_loc, str_size;
	if(cmd[1]=='\0')
    {
		char fp[bsize];
		pid_t proc_id = getpid();
		// /proc/<id>/stat contains the details of the programs 
		// running 
		FILE *file_point = fopen("/proc/self/stat", "r");
		//printf("self opens\n");

		// Here we use /proc/self/stat as self would give details of
		// the current process, i.e. the shell 
        if (file_point != NULL)
		    fscanf(file_point, "%s %s %s", pid, p_name, status);
		// printf("%d\t%s\t%s\n", pid, p_name, status);
        
		// /proc/<id>/statm contains the memory information of the
		// programs running
		file_point = fopen("/proc/self/statm", "r");
        if (file_point != NULL)
            fscanf(file_point, "%d", &file_in_loc);
        
		strcpy(fp,"/proc/self/exe");
		int length = readlink(fp, find_proc, sizeof(find_proc));
		find_proc[length] = '\0';
		printf("pid -- %d\n", proc_id);
		printf("Process Status -- %s\n", status);
		printf("Memory -- %d\n", file_in_loc);
		printf("Executable Path -- %s\n",find_proc);
	}
	else
    {
		// The same logic as above used here except that the user
		// gives the ID of the program that we have to check status of
		char file_path[bsize];
		strcpy(file_path, "/proc/");
		strcat(file_path, cmd[1]);
		strcat(file_path, "/stat");
		FILE *file_point = fopen(file_path, "r");
		if (file_point != NULL)
            fscanf(file_point, "%s %s %s", pid, p_name, status);
        else
		{
			printf("No such process exists\n");
			return;
		}
		
        strcpy(file_path, "/proc/");
		strcat(file_path, cmd[1]);
		strcat(file_path, "/statm");
		file_point = fopen(file_path, "r");
        if (file_point != NULL)
		    fscanf(file_point, "%d", &file_in_loc);
        
		strcpy(file_path, "/proc/");
		strcat(file_path, cmd[1]);
		strcat(file_path, "/exe");
		str_size = readlink(file_path, find_proc, sizeof(find_proc));
		find_proc[str_size] = '\0';
		printf("pid -- %s\n", cmd[1]);
		printf("Process Status -- %s\n", status);
		printf("Memory -- %d\n", file_in_loc);
		printf("Executable Path -- %s\n",find_proc);
	}
	return;
}