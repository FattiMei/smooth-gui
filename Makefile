CC      = gcc
CCFLAGS = -Wall -Werror
LIBS    = -lm -lglfw
INCLUDE = -I ./include


examples   = $(wildcard examples/*.c)
sources    = $(wildcard src/*.c)


targets    += $(patsubst %.c,build/%,$(examples))
targets    += $(patsubst src/%.c,build/%.o,$(sources))


all: $(targets)


build/examples/%: build/glad.o examples/%.c
	$(CC) $(INCLUDE) $(CFLAGS) -o $@ $^ $(LIBS)


build/%.o: src/%.c
	$(CC) $(INCLUDE) -c -o $@ $^


.PHONY: clean
clean:
	rm -rf $(targets)


.PHONY: folder
folder:
	mkdir -p build
	mkdir -p build/examples
