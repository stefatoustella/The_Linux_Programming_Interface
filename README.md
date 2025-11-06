# The Linux Programming Interface

This repository contains code examples and exercises from "The Linux Programming Interface" by Michael Kerrisk, a comprehensive guide to Linux and UNIX system programming.

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

### System Programming Concepts

- Process Creation and Program Execution
- Process Credentials
- File I/O Operations
- Files and Directories
- Process Groups, Sessions, and Job Control
- Signals and Timers
- Memory Allocation
- Time Measurement

### Key Programs

1. **Error Handling**

   - `error_functions.c`: Implementation of error handling functions
   - `ename.c.inc`: Error name handling

2. **Process Management**

   - `process_time.c`: Demonstration of process CPU time measurement
   - `p115.c`: Process relationships example
   - `p115a.c`: Orphaned process demonstration

3. **Time and Date**

   - `calendar_time.c`: Calendar time functions
   - `process_time.c`: Process time measurement

4. **File Operations**

   - `copy.c`: File copying implementation
   - `seek_io.c`: File seeking and I/O operations

5. **Memory Management**
   - `mem_segments.c`: Memory segments demonstration

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
- Linux-based operating system
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
