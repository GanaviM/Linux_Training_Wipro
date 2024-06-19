CC = gcc
CFLAGS = -I.
DEPS = add.h sub.h mul.h div.h
OBJ = main.o add.o sub.o mul.o div.o 

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)
main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)
