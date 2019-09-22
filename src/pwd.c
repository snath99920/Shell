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

// getcwd is the function that returns the current working directory
// of the shell. This fuction basically prints it, no big deal..
void PrintWorkingDirectory()
{
    char current_directory[10010];
    getcwd(current_directory, sizeof(current_directory));
    printf("%s\n", current_directory);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                          
    return;
}