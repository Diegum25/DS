#!/usr/bin/make

FILES = src/main.c
CFLAGS = -lcurl -Isrc

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