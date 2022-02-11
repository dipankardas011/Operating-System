CC=gcc
Wall=-g -Wall
# OPTIMIZATION=-O1

build: $@
	$(CC) $(Wall) $@

run:
	./a.out