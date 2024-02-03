CC      = gcc
CCFLAGS = -Wall -Werror
LIBS    = -lm -lglfw
INCLUDE = -I ./include


examples   = $(wildcard examples/*.c)


targets    += $(patsubst %.c,build/%,$(examples))


all: $(targets)


build/examples/%: examples/%.c
	$(CC) $(INCLUDE) $(CFLAGS) -o $@ $^ $(LIBS)


.PHONY: clean
clean:
	rm -rf $(targets)


.PHONY: folder
folder:
	mkdir -p build
	mkdir -p build/examples
