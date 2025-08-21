# PS/Networking — Simple C++ Sockets and Test HTTP Server

This project contains a minimal C++ socket abstraction and a simple HTTP server example that listens on localhost and returns a basic response.

## Features

- SimpleSocket: wraps socket() and address setup, enables SO_REUSEADDR (and SO_REUSEPORT if available).
- BindingSocket: binds a socket to an address/port and reports errors.
- ListeningSocket: starts listen() with a configurable backlog.
- ConnectingSocket: convenience client socket (not used by the test server).
- SimpleServer: base class that owns a ListeningSocket.
- TestServer: accepts one request, prints it to stdout, and responds with a minimal HTTP/1.1 response.

## Requirements

- Linux (POSIX sockets)
- g++ (tested on Fedora Linux)

## Build

- Build the test server binary (uses the relative include paths in the repo):


```bash
g++ Servers/test.cpp \
    Servers/SimpleServer.cpp Servers/TestServer.cpp \
    Sockets/BindingSocket.cpp Sockets/ConnectingSocket.cpp \
    Sockets/ListeningSocket.cpp Sockets/SimpleSocket.cpp \
    -o test.exe
```

Optionally add warnings/standard flags:

```bash
g++ -std=c++17 -Wall -Wextra -O2 \
    Servers/test.cpp Servers/SimpleServer.cpp Servers/TestServer.cpp \
    Sockets/BindingSocket.cpp Sockets/ConnectingSocket.cpp \
    Sockets/ListeningSocket.cpp Sockets/SimpleSocket.cpp \
    -o test.exe
```

## Run

- Start the server (default port: 8080):


```bash
./test.exe
```

- In another terminal, test with curl:

```bash
curl -v http://127.0.0.1:8080/
```

- Or open [http://127.0.0.1:8080/](http://127.0.0.1:8080/) in a browser.

## What you should see

- The server prints the incoming HTTP request to stdout, then sends a response:
  - Status: HTTP/1.1 200 OK
  - Headers: Content-Type: text/plain, Content-Length: 17, Connection: close
  - Body: "Hello from server"

## Troubleshooting

- Address already in use
  - The socket is created with SO_REUSEADDR, allowing quick restarts.
  - If the port is still held by another process, end it or kill by port:

    ```bash
    ss -tnlp | grep :8080
    fuser -k 8080/tcp
    ```

  - Alternatively, change the server port (see below).

- Permission denied binding to port 80
  - Ports < 1024 are privileged on Linux. Use a high port (e.g., 8080), or run with elevated privileges/capabilities.

- No output in the browser
  - Ensure the server is running and listening:

    ```bash
    ss -tnlp | grep :8080
    ```

  - Test with curl to see the raw response (see above).

## Change the port

- The port is set in Servers/TestServer.cpp in the TestServer constructor. Change `8080` to any available high port, rebuild, and rerun.

## Handles one request

- The example server currently accepts a single connection, prints and responds, then exits. To handle multiple requests, wrap the accept/handle/respond sequence in a loop or spawn per-connection handlers.

## Project structure

- Servers/
  - SimpleServer.hpp/.cpp: base server that owns a ListeningSocket
  - TestServer.hpp/.cpp: demo server that replies with a minimal HTTP response
  - test.cpp: program entry point
- Sockets/
  - SimpleSocket.hpp/.cpp: base socket wrapper (creates socket, sets options)
  - BindingSocket.hpp/.cpp: bind() and error checking
  - ListeningSocket.hpp/.cpp: listen() and backlog
  - ConnectingSocket.hpp/.cpp: connect() helper



