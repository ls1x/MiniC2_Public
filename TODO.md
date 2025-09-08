# MiniC2 RevShell Project

## Fixes
- [ ] Commands with large output will cause Segfault. For example: `cat /etc/passwd`
- [ ] There's a bug that the server message is multiple times executed in client after exiting. I currently don't know the cause.
- [X] Output of commands is not shown to the client side anymore.
- [X] There is an error when closing the sockets, this will cause the socket to remain open after program finished its execution.

## Improvements

## Future
- [ ] Make use of memory allocation functions instead of static char to store the messages and responses preventing Segfaults.
