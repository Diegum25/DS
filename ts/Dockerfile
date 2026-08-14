FROM ghcr.io/pnpm/pnpm:11

RUN pnpm runtime set node 22 -g

WORKDIR /ts

COPY ./src/ ./src/
# COPY ./Makefile ./Makefile
# this does not have make
COPY ./package.json ./package.json
COPY ./tsconfig.json ./tsconfig.json
COPY ./pnpm-lock.yaml ./pnpm-lock.yaml

RUN pnpm install --frozen-lockfile

RUN pnpm tsc

CMD node dist/main.js