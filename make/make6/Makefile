TARGET = test
CC = gcc

.PHONY: all clean
all: foo.c bar.c main.c
	$(CC) -o $(TARGET) $?

clean: 
	rm -f *.o