CC = gcc
CFLAGS = -I.
DEPS = main.h stack.h
OBJ = main.o stack.o

%o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)
