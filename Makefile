CC = gcc
CFLAGS = -Wall -Wextra -Iinclude -std=c11

SRC := $(wildcard src/*.c)
OBJ := $(patsubst src/%.c, build/obj/%.o, $(SRC))

TEST_SRC := $(wildcard tests/*.c)
TEST_BIN := build/tests/run_tests

.PHONY: all test clean

all: $(OBJ)

build/obj:
	mkdir -p build/obj

build/tests:
	mkdir -p build/tests

build/obj/%.o: src/%.c | build/obj
	$(CC) $(CFLAGS) -c $< -o $@

test: $(OBJ) $(TEST_SRC) | build/tests
	$(CC) $(CFLAGS) $(TEST_SRC) $(OBJ) -o $(TEST_BIN)
	./$(TEST_BIN)

clean:
	rm -rf build
