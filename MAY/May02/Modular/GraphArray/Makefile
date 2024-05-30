CC = gcc
CFLAGS = -I.
DEPS = graph.h
OBJ = main.o graph.o

%.o:%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)
graph: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

