CC=gcc

all: basic reverse

basic: basic.c slist.o
	$(CC) -g $^ -o $@

reverse: reverse.c slist.o
	$(CC) -g $^ -o $@

slist.o: slist.c
	$(CC) -c -fPIC -g $< -o $@

clean:
	rm -f slist.o
	rm -f reverse
	rm -f basic
