BIN = main
CC = g++

all: clean
	$(CC) -o $(BIN) $(shell fd '\.c$$') $(shell fd '\.cpp$$') $(shell fd '\.h$$')

clean: 
	rm -f $(BIN)
