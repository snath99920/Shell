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

void list(char ** cmd, int numC)
{
	int flag = 0;
	DIR *mydir;
	struct dirent *myfile;
	struct stat mystat;
	char buf[512], cwd[1024], comd[1024], path[100005];
	getcwd(cwd, sizeof(cwd));
	mydir = opendir(cwd);
	strcpy(comd,cmd[0]);
	for(int i = 1; i<numC; i++)
		strcat(comd,cmd[i]);
	if(strcmp(comd,"ls-a")==0 ||strcmp(comd,"ls-la")==0 || strcmp(comd,"ls-al")==0 ||strcmp(comd,"ls-l-a")==0 ||strcmp(comd,"ls-a-l")==0)
		flag = 1;
	int total = 0;
	while((myfile = readdir(mydir)) != NULL)
    {
		int fl=0;
		strcpy(path,cwd);
		strcat(path,"/");
		if(strcmp(comd,""))
			if(myfile->d_name[0] == 46 && (strcmp(comd,"ls")==0 || strcmp(comd,"ls-l")==0))
            {
				sprintf(buf, "%s/%s", path, myfile->d_name);
				stat(buf, &mystat);
				continue;
			}
		struct stat fstat={0};
		strcpy(path,cwd);
		strcat(path,"/");
		strcat(path,myfile->d_name);
		stat(path,&fstat);
		if(S_ISDIR(fstat.st_mode))
			fl=1;
		if(flag)
        {
			if(fl)
				printf("d");
			else
				printf("-");

			if(fstat.st_mode & S_IRUSR)
				printf("r");
			else
				printf("-");
			if(fstat.st_mode & S_IWUSR)
				printf("w");
			else
				printf("-");
			if(fstat.st_mode & S_IXUSR)
				printf("x");
			else
				printf("-");

			if(fstat.st_mode & S_IRGRP)
				printf("r");
			else
				printf("-");
			if(fstat.st_mode & S_IWGRP)
				printf("w");
			else
				printf("-");
			if(fstat.st_mode & S_IXGRP)
				printf("x");
			else
				printf("-");

			if(fstat.st_mode & S_IROTH)
				printf("r");
			else
				printf("-");
			if(fstat.st_mode & S_IWOTH)
				printf("w");
			else
				printf("-");
			if(fstat.st_mode & S_IXOTH)
				printf("x\t");
			else
				printf("-\t");

			struct passwd *pw = getpwuid(fstat.st_uid);
			struct group  *gr = getgrgid(fstat.st_gid);

			printf("%ld\t",fstat.st_nlink);

			struct tm lt;
			time_t t = mystat.st_mtime;
			localtime_r(&t, &lt);
			char timebuf[80];
			strftime(timebuf, sizeof(timebuf), "%c", &lt);

			printf("%s\t%s\t%s\t", pw->pw_name, gr->gr_name, timebuf);

			strcpy(path,cwd);
			strcat(path,"/");
			sprintf(buf, "%s/%s", path, myfile->d_name);
			stat(buf, &mystat);
			printf("%zu\t",mystat.st_size);
			
			total += mystat.st_blocks;
		}
		if(flag)
        {
			if(fl)
				printf(GREEN "%s" RESET "\n" , myfile->d_name);
			else
				printf("%s\n", myfile->d_name);
		}
		else
        {
			if(fl)
				printf(GREEN "%s" RESET "\t", myfile->d_name);
			else
				printf("%s\t", myfile->d_name);
		}
	}
    if(flag)
		printf("total %d\n",total/2);
	if(!flag)
		printf("\n");
	closedir(mydir);
}