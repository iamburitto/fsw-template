CC := gcc
CFLAGS := -std=c11 -Wall -Wextra -Werror -O2 -Iinclude

# all .c files in src/
SRC := $(wildcard src/*.c)

# convert src/foo.c -> build/foo.o
OBJ := $(patsubst src/%.c, build/%.o, $(SRC))

# all test source files
TEST_SRC := $(wildcard test/*.c)

# convert test/foo.c -> build/test_foo.o
TEST_OBJ := $(patsubst test/%.c, build/test_%.o, $(TEST_SRC))

# final binaries
TARGET := build/app
TEST_TARGET := build/test_runner

# default target builds the app (this fails if no main() in src/)
all: $(TARGET)

# link app from src object files ONLY (no main if src has none)
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@

# compile src .c -> .o
build/%.o: src/%.c
	@mkdir -p build
	$(CC) $(CFLAGS) -c $< -o $@

# compile test .c -> .o
build/test_%.o: test/%.c
	@mkdir -p build
	$(CC) $(CFLAGS) -c $< -o $@

# link test runner (includes test files, so has main())
test: $(OBJ) $(TEST_OBJ)
	$(CC) $(CFLAGS) $^ -o $(TEST_TARGET)
	./$(TEST_TARGET)

clean:
	rm -rf build

.PHONY: all test clean
