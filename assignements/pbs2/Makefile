COMPILER=gcc		# you can change your compiler to clang if you want to or dont have gcc
BIN_NAME=vectest

all:
	$(COMPILER) -g -fsanitize=address main.c vector.c -o $(BIN_NAME)

run:
	./$(BIN_NAME)

clean:
	rm $(BIN_NAME)