#!/usr/bin/make

FILES = src/main.c
CFLAGS = -lcurl -lm -lSDL3 -Icglm/include

.PHONY: all clean notimplemented

all: notimplemented

notimplemented:
	echo not implemented :p

build:
	mkdir -p build

build/client: $(FILES) | build
	gcc $(CFLAGS) $(FILES) -o$@

clean:
	rm -rf build