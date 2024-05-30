CC = gcc
CFLAGS = -I.
DEPS = bst.h
OBJ = bst.o main.o

%.o:%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)
bst: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

