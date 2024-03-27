CC=gcc
CFLAGS=-std=gnu99 -g -Wall -Wextra -Werror -pedantic 
LDFLAGS=-lrt -pthread

proj2: proj2.o
	$(CC) $(CFLAGS) proj2.c -o proj2 $(LDFLAGS)

clean:
	rm -f *.o *.out proj2
