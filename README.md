# ECE 252: Systems Programming and Concurrency

![C](https://img.shields.io/badge/language-C-blue.svg)
![OS](https://img.shields.io/badge/OS-Linux%20%7C%20POSIX-lightgrey.svg)
![Threads](https://img.shields.io/badge/Multithreading-POSIX%20Threads-brightgreen)
![Tools](https://img.shields.io/badge/Tools-Makefile%2C%20Valgrind%2C%20GDB-orange)
![License](https://img.shields.io/badge/license-MIT-lightgrey)

A series of systems programming assignments focused on low-level software concepts: memory management, concurrency, multithreading, and network communication in C.

---

## Topics Covered

* Process and thread management (POSIX)
* Inter-process synchronization with semaphores and mutexes
* Dynamic memory handling and debugging
* Socket programming and asynchronous I/O
* Systems-level tooling: Makefiles, Valgrind, Helgrind

---

## Project List

| Folder                              | Project Title           | Key Concepts                                                |
| ----------------------------------- | ----------------------- | ----------------------------------------------------------- |
| `01-command-line-utils`             | The Flash               | Command-line parsing, string manipulation                   |
| `02-file-io-and-pipes`              | Rogue One Socket Client | TCP sockets, `getaddrinfo`, stream I/O                      |
| `03-nqueens-multithreaded`          | N-Queens Solver         | Multithreaded search, pthreads, work partitioning           |
| `04-task-scheduler-synchronization` | Hogwarts Task Scheduler | Thread coordination, semaphores, mutexes                    |
| `05-valgrind-memory-debugging`      | The Time War            | Memory issues, race condition debugging with Valgrind tools |
| `06-async-io-network-server`        | Rogue Two (Server)      | `select()`, non-blocking I/O, concurrent client handling    |

---

## Build and Run

Each project includes a Makefile. Typical usage:

```bash
make
./main
```

Refer to each subfolder’s README for details on arguments and expected output.

---

## Debugging & Testing

* Memory use verified with `valgrind`
* Race conditions detected via `helgrind`
* Socket communication tested with multiple client inputs
* Thread interactions checked using concurrency stress cases

---

## Architecture Overview

```
+-----------------------------+
|        User Programs        |
|  (CLI tools, clients, tests) |
+-------------+---------------+
              |
              v
+-------------+---------------+
|     System Call Interface   |
|    (fork, pipe, pthreads)   |
+-------------+---------------+
              |
              v
+-------------+---------------+
|  Concurrency + Sync Layer   |
|   Threads, Mutexes, Semaphores |
+-------------+---------------+
              |
              v
+-------------+---------------+
|    I/O, Socket, and Memory  |
|  select(), malloc/free, file ops |
+-------------+---------------+
              |
              v
+-------------+---------------+
|          OS Kernel          |
+-----------------------------+
```

---

## About

This monorepo represents a complete course in systems programming with practical projects that emphasize reliability, performance, and correct concurrency behavior in C.
