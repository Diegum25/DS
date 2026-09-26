#!/usr/bin/make

FILES = src/main.c \
		src/info.c

CFLAGS = -lcurl -lm -lSDL3 -Wl,-rpath,'$$ORIGIN' -LcJSON -lcjson -Icglm/include -IcJSON -I../shared

FINALFLAGS = -O3 -s
DEBUGFLAGS = -ggdb

.PHONY: all cJSON clean cJSON/libcjson.so.1

all: build/client-final build/client-debug

build:
	mkdir -p build

# how do i make this one not run all the time
build/libcjson.so.1: cJSON/libcjson.so.1
	cp cJSON/libcjson.so.1 build/libcjson.so.1

# i would also like this to be static but i couldnt get it to link propperly
cJSON:
	$(MAKE) -C cJSON libcjson.so

build/client-final: $(FILES) cJSON | build build/libcjson.so.1
	gcc $(FINALFLAGS) $(CFLAGS) $(FILES) -o$@

build/client-debug: $(FILES) cJSON | build build/libcjson.so.1
	gcc $(DEBUGFLAGS) $(CFLAGS) $(FILES) -o$@

clean:
	rm build/client*