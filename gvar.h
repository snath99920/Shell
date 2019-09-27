#ifndef SHELL_H
#define SHELL_H
#define clear printf("\e[1;1H\e[2J");
#define GREEN "\x1B[32m"
#define RESET "\x1b[0m"

char *cmd[1000001];
char *history[25];
char Home[1024], line[1000001], present[100001];
int bg_pgm, end, hist_count, bg_len;
char *bg_pr[32768];
int bg_iter[32768];
pid_t process_now;

void displayShell();

int min(int x, int y);

void function_cd(char ** cmd);

void list(char ** cmd, int numC);

void pinfo(char ** cmd);

void redirect(char ** cmd, int noc);

int piped_exec(char ** cmd, int input_pipe, int fl, int left, int right);

void PrintWorkingDirectory();

void print_hist();

void bg_exe(char **cmd, int noc);

void echo(char ** cmd, int numC);

void set_env(char ** cmd, int noc);

void unset_env(char ** cmd, int noc);

void bf_func(char ** cmd, int noc);

void run_shell(char ** cmd,int noc);

void jobs(char ** cmd, int noc);

int get_id(int pid);

void kjob(char ** cmd, int noc);

void overkill(char ** cmd, int noc);

void sigint_handler(int s);

void nothing(int s);

void fg_bg(char ** cmd, int noc);

#endif
