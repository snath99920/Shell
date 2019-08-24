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

void displayShell()
{
    char host[100010], cur[100010];
    register uid_t user = geteuid();
    register struct passwd *passw = getpwuid(user);
    gethostname(host, sizeof(host));
    printf("<%s", passw->pw_name);
    printf("@%s", host);
    getcwd(present,sizeof(present));
    int len = strlen(present);
    int k = 0, i;
    if (strstr(present,Home))
        k = 1;
    // I have coded the value for GREEN in the header file gvar.h
    // Works like charm
    if (!strcmp(Home, present))
        printf(GREEN "~" RESET "> ");
    else if (len>end && k == 1)
        printf(GREEN "~%s" RESET "> ", present+end);
    else
        printf(GREEN "%s" RESET "> ", present);
}