CC = gcc
CFLAGS = -I.
DEPS = file_system.h
OBJ = file_system.o main.o

%.o:%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)
File: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

