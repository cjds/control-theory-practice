CC=gcc
CFLAGS=-I.
// DEPS = client.h

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

output: client.o
	g++ -o client client.o -I.
