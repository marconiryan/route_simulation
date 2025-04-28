# Routing Simulator

## Description
This project simulates a network of routers communicating with each other using **UDP sockets**.

Each router is an independent, multithreaded process capable of:
- Dynamically updating its routing table
- Sending and receiving data messages
- Adapting to changes in network topology (router activation and shutdown)

## Prerequisites
- **Operating System:** Linux
- **Compiler:** GCC (minimum support for C11)
- **CMake:** version 3.30 or higher (optional)

## File Structure
- `src/` - Contains all source files and headers organized into subfolders
- `config/roteador.config` - Configuration for router IPs and ports
- `config/enlaces.config` - Configuration for links and their costs
- `CMakeLists.txt` - Build a script for CMake

## Compilation

### Using CMake (recommended)
1. Create a build directory:
   ```bash
   mkdir build
   cd build
   ```

2. Generate build files:
   ```bash
   cmake ..
   ```

3. Compile:
   ```bash
   make
   ```

4. The executable `route_simulation` will be generated inside the `build/` directory.

---

### Manual Compilation (without CMake)

Alternatively, you can compile directly with `gcc`:

```bash
gcc -o route_simulation \
    src/main.c \
    src/links/links.c \
    src/router/router.c \
    src/utils/utils.c \
    src/server/server.c \
    src/queue/queue.c \
    src/client/client.c \
    src/blocking-queue/blocking-queue.c \
    src/terminal/terminal.c \
    src/message/message.c \
    -lpthread
```

**Note:** `-lpthread` is required for thread support.

The `route_simulation` binary will be created in the current directory.

---

## Execution

Run the program by passing the **router ID** as a parameter:

```bash
./route_simulation <ROUTER_ID>
```

Example:
```bash
./route_simulation 1
```

The ID must match the configuration defined in the `roteador.config` and `enlaces.config` files.

---

## Configuration Files

### roteador.config
Defines the routers and their UDP ports.

Format:
```
<ID> <PORT> <IP>
```
Example:
```
1 25001 127.0.0.1
2 25002 127.0.0.1
3 25003 127.0.0.1
4 25004 127.0.0.1
```

### enlaces.config
Defines the links between routers and the cost of each link.

Format:
```
<ID1> <ID2> <COST>
```
Example:
```
1 2 3
2 3 2
2 4 10
3 4 3
```

---

## Operation

When the program starts:
- It opens an interactive terminal with a menu of options.
- It displays sent and received messages and updates to the routing table.
- It allows sending messages of up to **100 characters** to other routers.

---

### Example of Sending a Message

**On the source router:**

```
========= MENU =========
1. Send message to neighbor
2. Exit
========================
Choose an option: 1
Available neighbors:
[2] -> cost: 0
[3] -> cost: 0
========================
Choose a neighbor: 2
Type the message: Hello, router 2!
Sent 17 bytes to 127.0.0.1:25002
Message: Hello, router 2!
```

**On the destination router:**

```
Waiting for messages on 127.0.0.1:25002...
Received 17 bytes from 127.0.0.1:47533
Message: Hello, router 2!
```