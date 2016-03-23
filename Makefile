all: invLogSum

invLogSum: invLogSum.c ibarland-utils.o command-line-options.o
	gcc -Wall invLogSum.c -o invLogSum ibarland-utils.o command-line-options.o -lm

command-line-options.o: command-line-options.c command-line-options.h ibarland-utils.o
	gcc -Wall -c command-line-options.c

ibarland-utils.o: ibarland-utils.c ibarland-utils.h
	gcc -Wall -c ibarland-utils.c

clean:
	rm -f  invLogSum  *.o

runC: invLogSum
	./invLogSum --num-threads 4

runJava:
	javac InvLogSum.java && java InvLogSum --num-threads 4