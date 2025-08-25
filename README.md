# MiniC2 Reverse Shell

This project includes the implementation of a primitive reverse shell, developed for educational purposes and hands-on learning in information security.

A reverse shell is a mechanism where a program running on a compromised machine (the client) initiates an outbound connection to a server controlled by the attacker, providing remote command-line access. Unlike a bind shell (which opens a listening port and waits for connections), a reverse shell is especially useful in scenarios where firewalls or NAT prevent direct inbound connections.

**Features of this reverse shell:**
- Outbound connection from the client to the server.
- Simple TCP-based communication.
- Basic ability to execute remote commands.
- Minimal implementation — no evasion or encryption mechanisms.

**Important Notice:**
- This reverse shell was developed strictly for study and testing in controlled environments (personal labs, virtual machines, etc.). It must not be used on real systems without explicit authorization.

## Compilation:
- `gcc tcp-client.c -o tcp-client.bin`
- `gcc tcp-server.c -o tcp-server.bin`

## Usage:
- Launch the `tcp-server` on attacker machine: `./tcp-server.bin`
- Launch the `tcp-client` on target machine: `./tcp-client.bin`
