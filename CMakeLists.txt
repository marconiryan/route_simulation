cmake_minimum_required(VERSION 3.22.1)
project(route_simulation C)

set(CMAKE_C_STANDARD 11)

add_executable(
        route_simulation src/main.c
        src/links/links.c
        src/links/links.h
        src/router/router.c
        src/router/router.h
        src/utils/utils.c
        src/utils/utils.h
        src/server/server.c
        src/server/server.h
        src/queue/queue.c
        src/queue/queue.h
        src/client/client.c
        src/client/client.h
        src/blocking-queue/blocking-queue.c
        src/blocking-queue/blocking-queue.h
        src/terminal/terminal.c
        src/terminal/terminal.h
        src/message/message.c
        src/message/message.h
)
