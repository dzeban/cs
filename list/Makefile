CC=gcc

all: basic reverse

basic: basic.c list.o
	$(CC) -g $^ -o $@

reverse: reverse.c list.o
	$(CC) -g $^ -o $@

list.o: list.c
	$(CC) -c -fPIC -g $< -o $@

clean:
	rm -f list.o
	rm -f reverse
	rm -f basic
