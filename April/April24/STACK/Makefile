CC = gcc
CFLAGS = -I.
DEPS = pop.h push.h isempty.h isfull.h stack.h main.h
OBJ = pop.o push.o isempty.o isfull.o stack.o main.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

stacking: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)
