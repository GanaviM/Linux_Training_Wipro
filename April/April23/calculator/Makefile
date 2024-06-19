CC = gcc
CFLAGS = -I.
OBJ = main.o add.o sub.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)
main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)
