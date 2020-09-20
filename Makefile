# variable assignment for the program we’re building:
target = render

# Cross Compiler
CC=g++
# Basic flags for compiling:
CFLAGS = -std=c++17 -Wall
# Optional stricter flags:
CFLAGS += -Wextra -Wpedantic -Werror -Wfatal-errors
# Optional debug flags
DEBUGFLAGS = -g -ggdb -O0
# Includes:
INCLUDEFLAGS = -lm -Ilib -Iinclude

# Build args
build:
	CFLAGS += -03
	$(target)
debug: 
	CFLAGS += DEBUGFLAGS
	$(target)

# Target recipes
$(target): render.o
	$(CC) -o $@ $^ $(CFLAGS) $(INCLUDEFLAGS)

# Dependency recipes
%.o: %.C %.h
	$(CC) -c -o build/$@ src/$< $(CFLAGS) $(INCLUDEFLAGS)

# This phony targets
clean:
	@rm -f build/*.o $(target)
