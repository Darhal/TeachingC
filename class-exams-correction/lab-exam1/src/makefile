#LLVM=$(brew --prefix llvm)
LLVM=/usr/local/opt/llvm
#LLVM=/usr
CC=$(LLVM)/bin/clang
#CFLAGS=-std=c18 -Wall -Werror -Wextra -pedantic
CFLAGS=-Wall -Wextra -pedantic 
LDFLAGS=-L$(LLVM)/lib
CPPFLAGS=-I$(LLVM)/include

RELEASE ?= 0
ifeq ($(RELEASE), 0)
	CFLAGS += $(CPPFLAGS) -O0 -g3 -fsanitize=address -fno-omit-frame-pointer -fno-optimize-sibling-calls
else
	CFLAGS += -DNDEBUG -O3
endif

.PHONY: clean run

all: main test_snow

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

main: main.o library.o book.o
	$(CC) $(CFLAGS) $^ -o $@

test_snow: test_snow.c library.o book.o
	$(CC) $(CFLAGS) -DSNOW_ENABLED $(QUESTIONS_FLAG) $^ -o $@

clean:
	@rm -f *.o main test_snow

run: main
	@LSAN_OPTIONS=detect_leaks=1 ASAN_SYMBOLIZER_PATH=$(LLVM)/bin/llvm-symbolizer ASAN_OPTIONS=symbolize=1 ./$<

test: test_snow
	@LSAN_OPTIONS=detect_leaks=1 ASAN_SYMBOLIZER_PATH=$(LLVM)/bin/llvm-symbolizer ASAN_OPTIONS=symbolize=1 ./$<
