CC      = gcc
CCFLAGS = -Wall -Werror
LIBS    = -lm -lglfw -ldl
INCLUDE = -I ./include


examples   = $(wildcard examples/*.c)
sources    = $(wildcard src/*.c)
objects    = $(patsubst src/%.c,build/%.o,$(sources))


targets    += $(patsubst %.c,build/%,$(examples))
targets    += $(objects)


all: $(targets)


build/examples/%: $(objects) examples/%.c
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
