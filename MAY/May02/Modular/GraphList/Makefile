CC = gcc
CFLAGS = -I.
DEPS = graph.h
OBJ = graph.o main_list.o

%.o:%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)
graph: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)


