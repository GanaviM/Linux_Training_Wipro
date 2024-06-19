CC = gcc
CFLAGS =-I.
DEPS = gps_parser.h
OBJ = gps_parser.o main.o

%.o: %c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

parse: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)
