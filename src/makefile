CC=gcc
CFLAGS=-Wall -Wextra -Wpedantic -I/opt/homebrew/Cellar/sdl2_gfx/1.0.4/include -I/opt/homebrew/include -I/opt/homebrew/include/SDL2
LDFLAGS=-L/opt/homebrew/Cellar/sdl2_gfx/1.0.4/lib -L/opt/homebrew/lib
LDLIBS=-lSDL2_gfx -lSDL2 -lm -ldl

all: runmac

runmac: engine.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^ $(LDLIBS)

.PHONY: clean

clean:
	rm -f runmac
