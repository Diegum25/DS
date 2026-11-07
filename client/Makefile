#!/usr/bin/make

UTILFILES = src/ray.c \
		src/pixel.c \
		src/sphere.c \
		src/image.c \
		src/camera.c \
		src/info.c \
		src/hittable.c \
		src/list.c

CFLAGS = -Wall -Wextra -Icglm/include -IcJSON -I../shared
LFLAGS = -lcurl -lm -lSDL3

FINALCFLAGS = -O3 -s $(CFLAGS)
DEBUGCFLAGS = -g -ggdb $(CFLAGS)

.PHONY: all cJSON clean

all: build/client-final build/client-debug

build:
	mkdir -p build

cJSON:
	$(MAKE) -C cJSON libcjson.a

build/client-final: $(UTILFILES) cJSON src/main.c | build
	gcc $(FINALCFLAGS) $(UTILFILES) src/main.c cJSON/libcjson.a $(LFLAGS) -o$@

build/client-debug: $(UTILFILES) cJSON src/main.c | build
	gcc $(DEBUGCFLAGS) $(UTILFILES) src/main.c cJSON/libcjson.a $(LFLAGS) -o$@

build/rays: $(UTILFILES) src/balanceddemo.c | build
	gcc $(DEBUGCFLAGS) $(UTILFILES) src/balanceddemo.c $(LFLAGS) -o$@

build/bounce: $(UTILFILES) src/bouncedemo.c | build
	gcc $(DEBUGCFLAGS) $(UTILFILES) src/bouncedemo.c $(LFLAGS) -o$@

clean:
	echo not implemented :P
