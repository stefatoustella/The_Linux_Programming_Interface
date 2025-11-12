# The Linux Programming Interface

This repository contains code examples and exercises from "The Linux Programming Interface" by Michael Kerrisk, a comprehensive guide to Linux and UNIX system programming. This is a working repository implementing various Linux system programming concepts.

## About the Book

"The Linux Programming Interface" (TLPI) is the definitive guide to Linux and UNIX system programming. Some key aspects of the book include:

- **Author**: Michael Kerrisk
- **Publication Date**: October 2010
- **Publisher**: No Starch Press
- **Pages**: 1552
- **ISBN**: 978-1593272203

## Book Overview

The book provides detailed coverage of:

- Linux system calls
- The Linux programming API
- Fundamental concepts of Linux programming
- System programming concepts for Linux

## Repository Structure

This repository contains implementations and exercises from the book, including:

### Implemented System Programming Concepts

1. **Process Management**

   - Process Creation and Execution (`p114.c`, `p115.c`)
   - Process Relationships (`p115.c`, `p115a.c`)
   - Process Times (`process_time.c`)

2. **Memory Management**

   - Memory Segments (`mem_segments.c`)
   - Dynamic Memory Allocation (`free_and_sbrk.c`)
   - Program Break Manipulation (`free_and_sbrk.c`)

3. **Time and Date**

   - Calendar Time (`calendar_time.c`)
   - Time Functions (`p187.c`, `p187a.c`)
   - Process CPU Time (`process_time.c`)

4. **File Operations**

   - Basic I/O (`p48.c`)
   - File Copying (`copy.c`)
   - File Seeking (`seek_io.c`)

5. **User and Group Information**
   - Process Credentials (`idshow.c`)
   - User/Group Functions (`ugid_functions.c`)

### Core Components and Libraries

1. **Header Files**

   - `tlpi_hdr.h`: Common definitions and includes
   - `error_functions.h`: Error handling prototypes
   - `get_num.h`: Number parsing declarations
   - `ugid_functions.h`: User/Group function declarations

2. **Library Source Files**

   - `error_functions.c`: Error handling framework
   - `get_num.c`: Command-line number parsing
   - `ugid_functions.c`: User/Group ID utilities
   - `ename.c.inc`: Error name mappings

3. **Static Libraries**

   - `liberr.a`: Error handling functions
   - `libugid.a`: User/Group ID utilities

4. **Build System**
   - `Makefile`: Build rules and targets

## Building and Running

This section collects recommended, copy‑pasteable compile/link/run commands you can use for programs in this repository. Many examples require POSIX/GNU feature macros (so prototypes such as `vfork()`, `strsignal()` or `basename()` are visible) — the commands below define them on the compiler command line. If `tlpi_hdr.h` already defines those macros before system includes, you can omit them.

General flags used in the examples:

- -D_POSIX_C_SOURCE=200809L — make POSIX APIs visible
- -D_GNU_SOURCE — enable GNU extensions (optional)
- -Wall -Wextra — useful warnings
- -std=c11 — C standard (adjust if needed)
- -g — include debug symbols (optional)
- -O2 — optimize (optional)

1. Simple single-source program

- Compile and link:
  gcc -D_POSIX_C_SOURCE=200809L -Wall -Wextra -std=c11 \
   -o program_name program_name.c
- Run:
  ./program_name

2. Program using the minimal TLPI helpers (error_stub.c)

- If you use the provided minimal helpers (error_stub.c):
  gcc -D_POSIX_C_SOURCE=200809L -Wall -Wextra -std=c11 \
   -o program_name program_name.c error_stub.c
  ./program_name

3. Program using the real TLPI helper sources (error_functions.c, get_num.c)

- Link helper sources instead of the stub:
  gcc -D_POSIX_C_SOURCE=200809L -Wall -Wextra -std=c11 \
   -o program_name program_name.c error_functions.c get_num.c
  ./program_name

4. Two-step compile (object files then link)

- Compile to objects:
  gcc -D_POSIX_C_SOURCE=200809L -Wall -Wextra -std=c11 -c file1.c -o file1.o
  gcc -D_POSIX_C_SOURCE=200809L -Wall -Wextra -std=c11 -c file2.c -o file2.o
- Link:
  gcc -o program_name file1.o file2.o error_stub.c
- Run:
  ./program_name

5. Static libraries (liberr.a, libugid.a) and -I include

- If you have prebuilt archives:
  gcc -D_POSIX_C_SOURCE=200809L -Wall -Wextra -std=c11 \
   -I. -o program_name program_name.c -L. -lerr -lugid
  Or link directly with archives:
  gcc -D_POSIX_C_SOURCE=200809L -Wall -Wextra -std=c11 \
   -I. -o program_name program_name.c liberr.a libugid.a

6. Building specific examples from this repository

- t_vfork

  - If using error_stub.c:
    gcc -D_POSIX_C_SOURCE=200809L -Wall -Wextra -std=c11 \
     -o t_vfork t_vfork.c error_stub.c
    ./t_vfork
  - If using TLPI helpers:
    gcc -D_POSIX_C_SOURCE=200809L -Wall -Wextra -std=c11 \
     -o t_vfork t_vfork.c error_functions.c get_num.c
    ./t_vfork

- make_zombie
  gcc -D_POSIX_C_SOURCE=200809L -Wall -Wextra -std=c11 \
   -o make_zombie make_zombie.c error_stub.c
  ./make_zombie

- print_wait_status (with its test driver test_wait.c)
  gcc -D_GNU_SOURCE -D_POSIX_C_SOURCE=200809L -Wall -Wextra -std=c11 \
   -o print_wait_status test_wait.c print_wait_status.c error_stub.c
  ./print_wait_status

- t_system (interactive system wrapper)
  gcc -D_GNU_SOURCE -D_POSIX_C_SOURCE=200809L -Wall -Wextra -std=c11 \
   -o t_system t_system.c print_wait_status.c error_stub.c
  ./t_system

- system_case_study using custom system() (if you keep `system.c` and want to override libc's symbol)

  # If you compiled system.c already to system.o:

  gcc -D_GNU_SOURCE -D_POSIX_C_SOURCE=200809L -Wall -Wextra -std=c11 \
   -o system system_case_study.c system.o print_wait_status.c error_stub.c
  ./system

  # Or build all at once from sources:

  gcc -D_GNU_SOURCE -D_POSIX_C_SOURCE=200809L -Wall -Wextra -std=c11 \
   -o system system_case_study.c system.c print_wait_status.c error_stub.c
  ./system
  NOTE: defining a local `system` overrides libc's `system()` for that executable. If you do not want that, rename `system.c` (e.g., to `my_system.c`) and use the `my_system()` variant provided in some examples.

- system_case_study using renamed `my_system.c`
  gcc -D_GNU_SOURCE -D_POSIX_C_SOURCE=200809L -Wall -Wextra -std=c11 \
   -o system_case_study_my system_case_study_my.c my_system.c print_wait_status.c error_stub.c
  ./system_case_study_my

7. Using precompiled object files (you already made system.o)

- Compile other sources:
  gcc -D_GNU_SOURCE -D_POSIX_C_SOURCE=200809L -Wall -Wextra -std=c11 -c print_wait_status.c -o print_wait_status.o
  gcc -D_GNU_SOURCE -D_POSIX_C_SOURCE=200809L -Wall -Wextra -std=c11 -c system_case_study.c -o system_case_study.o
- Link using the prebuilt system.o:
  gcc -o system system_case_study.o system.o print_wait_status.o error_stub.c
  ./system

8. Using the repository Makefile (recommended for many programs)

- If a `Makefile` exists with targets:
  make # build default/all targets
  make print_wait_status
  make t_vfork
  make clean # remove binaries/objects
- The Makefile in this repo typically sets feature macros and lists helper objects; inspect it or edit to add new targets.

9. Feature-test macros and redefinition warnings

- If you define `_GNU_SOURCE` or `_POSIX_C_SOURCE` in source files (via `#define`) and also on the command line, the compiler may warn about redefinitions. To avoid warnings, either:
  - define macros on the compiler command line only (preferred), or
  - guard in source: `#ifndef _GNU_SOURCE / #define _GNU_SOURCE / #endif`.

10. Debugging, tracing, and verification

- Add debug symbols:
  gcc -g ...
- Inspect a built executable:
  file ./program_name
  ls -l ./program_name
- Trace system calls:
  strace -f ./program_name
- Use valgrind for memory checks:
  valgrind ./program_name

## Dependencies

- GCC (GNU Compiler Collection)
- Make (for building multiple programs)
- Standard Linux development headers (glibc development, etc.)

## Notes

- Executable files and object files (\*.o) are excluded from the repository
- Each program demonstrates specific aspects of Linux system programming
- Comments in the code provide additional explanation of concepts
- Be cautious when overriding libc functions (e.g., `system`) — prefer renaming (e.g., to `my_system`) for safe testing

## References

1. The Linux Programming Interface: [Official Page](https://man7.org/tlpi/)
2. Man7.org - Michael Kerrisk's site: [https://man7.org/](https://man7.org/)
3. Linux man-pages project: [https://www.kernel.org/doc/man-pages/](https://www.kernel.org/doc/man-pages/)

## License

This code is for educational purposes and follows the examples from "The Linux Programming Interface" book. Please refer to the book's license for usage terms.

---

_Note: This repository contains my implementations of exercises and examples from the book as part of my learning journey. For the official code examples, please visit the [official TLPI page](https://man7.org/tlpi/)._
