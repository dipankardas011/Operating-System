CC=gcc
Wall=-g -Wall
EXEC=a.out


build: *.h *.c
	$(CC) $(Wall) CPUmain.c

run:
	./$(EXEC) --n

runDebug:
	./$(EXEC) --d

help:
	./$(EXEC)

clean:
	rm *.out