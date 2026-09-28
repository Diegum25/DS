#!/usr/bin/make

FILES = src/main.c \
		src/info.c

CFLAGS = -lcurl -lm -lSDL3 -Icglm/include -IcJSON -I../shared

FINALFLAGS = -O3 -s
DEBUGFLAGS = -ggdb

.PHONY: all cJSON clean

all: build/client-final build/client-debug

build:
	mkdir -p build

cJSON:
	$(MAKE) -C cJSON libcjson.a

build/client-final: $(FILES) cJSON | build
	gcc $(FINALFLAGS) $(CFLAGS) $(FILES) cJSON/libcjson.a -o$@

build/client-debug: $(FILES) cJSON | build
	gcc $(DEBUGFLAGS) $(CFLAGS) $(FILES) cJSON/libcjson.a -o$@

clean:
	rm build/client*