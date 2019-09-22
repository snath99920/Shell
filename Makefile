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
			min.o
		$(CC) -g -o shell $^
clean:
	@rm -f *.o shell

main.o: gvar.h main.c
	$(CC) -g -c main.c

cd.o: gvar.h src/cd.c
	$(CC) -g -c src/cd.c

exec.o: gvar.h src/bg.c
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