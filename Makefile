CC      = gcc
CCFLAGS = -Wall -Werror
LIBS    = -lm -lglfw -lEGL -lGL
INCLUDE = -I ./include


examples   = $(wildcard examples/*.c)
sources    = $(wildcard src/*.c)
objects    = $(patsubst src/%.c,build/%.o,$(sources))


targets    += $(patsubst %.c,build/%,$(examples))
targets    += $(objects)


all: $(targets)


build/examples/hello: examples/hello.c
	$(CC) $(INCLUDE) $(CCFLAGS) -o $@ $^ $(LIBS)


build/examples/gui: build/shader.o build/slider.o examples/gui.c
	$(CC) $(INCLUDE) $(CCFLAGS) -o $@ $^ $(LIBS)


build/examples/%: $(objects) examples/%.c
	$(CC) $(INCLUDE) $(CCFLAGS) -o $@ $^ $(LIBS)


build/%.o: src/%.c
	$(CC) $(INCLUDE) $(CCFLAGS) -c -o $@ $^ $(LIBS)


.PHONY: clean
clean:
	rm -rf $(targets)


.PHONY: folder
folder:
	mkdir -p build
	mkdir -p build/examples
