CC      = gcc
CCFLAGS = -Wall -Werror
LIBS    = -lm -lglfw -lEGL -lGL
INCLUDE = -I ./include


sources        = $(wildcard src/*.c)
examples       = $(wildcard examples/*.c)


objects    = $(patsubst src/%.c,build/%.o,$(sources))


targets    += $(patsubst %.c,build/%,$(examples))
targets    += $(objects)


all: $(targets)


build/examples/gui: build/shader.o build/slider.o examples/gui.c
	$(CC) $(INCLUDE) $(CCFLAGS) -o $@ $^ $(LIBS)


build/examples/hello: build/window.o examples/hello.c
	$(CC) $(INCLUDE) $(CCFLAGS) -o $@ $^ $(LIBS)


build/examples/texture: build/window.o build/shader.o examples/texture.c
	$(CC) $(INCLUDE) $(CCFLAGS) -o $@ $^ $(LIBS)


build/examples/triangle: build/window.o build/shader.o examples/triangle.c
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
