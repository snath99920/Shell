#ifndef SHELL_H
#define SHELL_H
#define clear printf("\e[1;1H\e[2J");
#define GREEN "\x1B[32m"
#define RESET "\x1b[0m"
<<<<<<< HEAD
// #define min(a,b) (a<b?a:b)
=======
>>>>>>> 1b496aaeb0097cca56aaef55ad1f99a6aaf6abfa

char *cmd[1000001];
char *history[25];
char Home[1024], line[1000001], present[100001];
int bg_pgm, end, hist_count;

void displayShell();

<<<<<<< HEAD
int min(int x, int y);

=======
>>>>>>> 1b496aaeb0097cca56aaef55ad1f99a6aaf6abfa
void function_cd(char ** cmd);

void list(char ** cmd, int numC);

void pinfo(char ** cmd);

<<<<<<< HEAD
void redirect(char ** cmd, int noc);

int piped_exec(char ** cmd, int input_pipe, int fl, int left, int right);

=======
>>>>>>> 1b496aaeb0097cca56aaef55ad1f99a6aaf6abfa
void PrintWorkingDirectory();

void print_hist();

void bg_exe(char **cmd, int noc);

void echo(char ** cmd, int numC);

void run_shell(char ** cmd,int noc);

#endif
