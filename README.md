# ECE 252: Systems Programming and Concurrency — Assignments

This repository contains a collection of assignments completed as part of the ECE 252 course at the University of Waterloo. The course focuses on systems-level programming in C, exploring topics such as:

- Low-level memory management
- Multithreading and concurrency
- POSIX threads and synchronization (mutexes, semaphores)
- Networking with sockets
- Asynchronous I/O with `select()` and `poll()`
- Debugging tools like Valgrind and Helgrind

Each assignment demonstrates one or more of these core systems programming concepts.

## Assignments

| Folder | Title                       | Topics Covered                              |
|--------|-----------------------------|---------------------------------------------|
| a1     | The Flash                   | Basic C, command-line parsing               |
| 02-file-io-and-pipes         | Rogue One Socket Client                  | Socket programming in C, TCP/IP networking, `getaddrinfo`, and client-server communication |
| a3     | N-Queens Problem            | POSIX threads, concurrency                  |
| a4     | Hogwarts Task Scheduler     | Threads, semaphores, mutexes                |
| a5     | The Time War                | Memory debugging, race conditions, Valgrind |
| a6     | Rogue Two (Server)          | Network sockets, asynchronous I/O           |

Each assignment directory includes source code, a Makefile, and a README with instructions on how to build and run the project.

---

**Note:** This monorepo is intended for showcasing systems programming proficiency and C programming skills, particularly with concurrency and low-level I/O.

