CC = gcc
CFLAGS = -Wall -g
SRCS = *.c
HEADERS = headers/*.h
FLAGS = -oFast
EXE = blackjack21

all:
	$(CC) $(FLAGS) $(SRCS) -o $(EXE)

.PHONY: clean

clean:
	rm -f $(OBJ) blackjack21