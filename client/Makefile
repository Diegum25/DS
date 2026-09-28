#!/usr/bin/make

FILES = src/main.c \
		src/info.c

CFLAGS = -lcurl -lm -lSDL3 -Icglm/include -IcJSON -I../shared

BUILD = gcc $(FINALFLAGS) $(CFLAGS) $(FILES) cJSON/libcjson.a

FINALFLAGS = -O3 -s
DEBUGFLAGS = -ggdb

.PHONY: all cJSON clean

all: build/client-final build/client-debug

build:
	mkdir -p build

cJSON:
	$(MAKE) -C cJSON libcjson.a

build/client-final: $(FILES) cJSON | build
	$(BUILD) -o$@

build/client-debug: $(FILES) cJSON | build
	$(BUILD) -o$@

clean:
	rm build/client*