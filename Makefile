CFLAGS = -Wall -Wextra -pedantic -Ofast -flto -march=native
LDFLAGS = -lm
CC = gcc
LIBS = lib/Tinn.c

all:
	$(CC) -o app pc_main.cpp $(LIBS) $(CFLAGS) $(LDFLAGS)

run:
	./$(BIN)

clean:
	rm -f $(BIN)
