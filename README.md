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

To compile any program:

```bash
gcc -Wall -o program_name program_name.c
```

For programs that use the error functions library:

```bash
gcc -Wall -I. -o program_name program_name.c liberr.a
```

## Dependencies

- GCC (GNU Compiler Collection)
- Make (for building multiple programs)

## Notes

- Executable files and object files (\*.o) are excluded from the repository
- Each program demonstrates specific aspects of Linux system programming
- Comments in the code provide additional explanation of concepts

## References

1. The Linux Programming Interface: [Official Page](https://man7.org/tlpi/)
2. Man7.org - Michael Kerrisk's site: [https://man7.org/](https://man7.org/)
3. Linux man-pages project: [https://www.kernel.org/doc/man-pages/](https://www.kernel.org/doc/man-pages/)

## License

This code is for educational purposes and follows the examples from "The Linux Programming Interface" book. Please refer to the book's license for usage terms.

---

_Note: This repository contains my implementations of exercises and examples from the book as part of my learning journey. For the official code examples, please visit the [official TLPI page](https://man7.org/tlpi/)._
