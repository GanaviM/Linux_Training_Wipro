CC = gcc
CFLAGS =-I.
DEPS = sort_strings.h main.h
OBJ = sort_strings.o main.o

%.o:%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

SORT: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)
