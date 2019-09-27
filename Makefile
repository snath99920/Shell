shell: \
			main.o \
			cd.o \
			bg.o \
			execute.o \
			list.o \
			pinfo.o \
			displayShell.o \
			pwd.o \
			echo.o \
			history.o\
			redirect.o\
			pipes.o\
			min.o\
			signal.o\
			job_id.o\
			kjob.o\
			jobs.o\
			overkill.o\
			fg_bg.o\
			env_set.o\
			unset_env.o\
			bg_f.o
			
		$(CC) -g -o shell $^
clean:
	@rm -f *.o shell

main.o: gvar.h main.c
	$(CC) -g -c main.c

job_id.o: gvar.h src/job_id.c
	$(CC) -g -c src/job_id.c

kjob.o: gvar.h src/kjob.c
	$(CC) -g -c src/kjob.c

jobs.o: gvar.h src/jobs.c
	$(CC) -g -c src/jobs.c

bg_f.o: gvar.h src/bg_f.c
	$(CC) -g -c src/bg_f.c

overkill.o: gvar.h src/overkill.c
	$(CC) -g -c src/overkill.c

fg_bg.o: gvar.h src/fg_bg.c
	$(CC) -g -c src/fg_bg.c

unset_env.o: gvar.h src/unset_env.c
	$(CC) -g -c src/unset_env.c

env_set.o: gvar.h src/env_set.c
	$(CC) -g -c src/env_set.c

cd.o: gvar.h src/cd.c
	$(CC) -g -c src/cd.c

bg.o: gvar.h src/bg.c
	$(CC) -g -c src/bg.c

execute.o: gvar.h src/execute.c
	$(CC) -g -c src/execute.c

list.o: gvar.h src/list.c
	$(CC) -g -c src/list.c

pinfo.o: gvar.h src/pinfo.c
	$(CC) -g -c src/pinfo.c

displayShell.o: gvar.h src/displayShell.c
	$(CC) -g -c src/displayShell.c

pwd.o: gvar.h src/pwd.c
	$(CC) -g -c src/pwd.c

echo.o: gvar.h src/echo.c
	$(CC) -g -c src/echo.c

history.o: gvar.h src/history.c
	$(CC) -g -c src/history.c
	
redirect.o: gvar.h src/redirect.c
	$(CC) -g -c src/redirect.c

pipes.o: gvar.h src/pipes.c
	$(CC) -g -c src/pipes.c
	
min.o: gvar.h src/min.c
	$(CC) -g -c src/min.c

signal.o: gvar.h src/signal.c
	$(CC) -g -c src/signal.c