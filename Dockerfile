# like a baws

FROM alpine:latest AS builder

RUN apk update && apk upgrade

RUN apk add git make sdl3-dev curl-dev build-base

WORKDIR /DS

# copy everything get those modules
COPY . .

RUN make -C client/ build/rays

# stage 2

FROM alpine:latest

RUN apk update && apk upgrade

RUN apk add sdl3 curl

WORKDIR /DS

COPY --from=builder /DS/client/build build
