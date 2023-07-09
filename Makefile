
all: shell.o compile_binaries

shell.o: shell.c
	gcc -o shell shell.c -lpthread

compile_binaries: cat.o ls.o rm.o mkdir.o date.o

cat.o: cat.c
	gcc -o cat cat.c
	
ls.o: ls.c
	gcc -o ls ls.c

rm.o: rm.c
	gcc -o rm rm.c

mkdir.o: mkdir.c
	gcc -o mkdir mkdir.c

date.o: date.c
	gcc -o date date.c

clean:
	rm shell cat ls date rm mkdir *.o
