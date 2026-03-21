# Contributing to The-JLC-Project

Welcome! **The-JLC-Project** is a collection of minimalist C utilities inspired by *UNIX philosophy* and *suckless software principles*. We value **simplicity**, **efficiency**, and **clarity** above all else. Contributions must align with these core tenets to maintain the project's integrity.

## Core Principles

### UNIX Philosophy
- **Do one thing and do it well**: Each utility in this project should focus on a single, well-defined task. Avoid feature creep or combining unrelated functionalities. For example, if a tool handles file copying, it shouldn't also perform sorting or filtering unless those are essential to the core task.
- Keep implementations modular and composable, allowing tools to be chained via pipes or scripts for complex workflows.

### Suckless Software Laws
We adhere to the [suckless.org](https://suckless.org) philosophy, which emphasizes:
- **Simplicity**: Code should be straightforward, readable, and free of unnecessary abstractions. Avoid over-engineering—prefer direct solutions over complex frameworks.
- **Minimalism**: Strip away bloat. No dependencies on heavy libraries unless absolutely required. Prioritize self-contained, portable code.
- **Correctness**: Code must be robust, secure, and bug-free. Test thoroughly, and avoid hacks or workarounds.
- **Transparency**: Everything should be auditable. No hidden behaviors, magic numbers, or opaque logic.
- **Sucklessness**: Reject "suck" (unnecessary complexity, inefficiency, or poor design). If something feels bloated, refactor it.

Contributions that violate these laws (e.g., adding unnecessary features, increasing complexity, or ignoring portability) will be rejected.

---

## Code Guidelines

### Size Constraints
- **Maximum lines per code piece**: Every function, module, or standalone code unit must be **100 lines or fewer**. This enforces focus and readability. Break larger logic into smaller, composable functions.
- "Code piece" refers to individual functions or small modules (e.g., a single utility's `main` or a helper). Entire files can be longer if they contain multiple small pieces, but each piece must adhere to the limit.
- **Exceptions**: Comments, blank lines, and preprocessor directives (e.g., `#include`) do not count toward the line limit.
- **Rationale**: Large functions are harder to understand, test, and maintain. This rule promotes the UNIX principle and suckless minimalism.

### Header Files
- **Maximum header files per utility**: Each utility (e.g., a single `.c` file and its dependencies) must include **5 header files or fewer**.
- This includes standard library headers (e.g., `<stdio.h>`, `<stdlib.h>`) and any custom headers.
- Avoid pulling in unnecessary headers—only include what's essential for the task.
- **Rationale**: Excessive includes lead to bloated binaries and slower compilation. It also encourages self-sufficiency and reduces dependencies.

### General Coding Standards
- **Language**: C (standard C99 for portability).
- **Style**: Follow K&R style (as in the Linux kernel or suckless projects). Use tabs for indentation, no trailing whitespace, and consistent naming (`snake_case` for variables/functions).
- **Error Handling**: Use simple, explicit checks. Avoid exceptions or complex error propagation—return codes or `errno` suffice. Always use `fprintf(stderr, ...)` for error/usage messages, never `printf`.
- **Exit Codes**: Use incrementing integer exit codes starting from 1 (e.g., return 1 for usage error, 2 for file open failure, 3 for I/O failure). This ensures consistent and predictable error signaling across utilities.
- **Memory Management**: Manual allocation/deallocation only. No garbage collection or smart pointers. Free resources promptly to prevent leaks. Always check `malloc`/`realloc`/`strdup` return values for `NULL`.
- **Portability**: Code must compile on POSIX systems (Linux, BSD, etc.) without platform-specific extensions unless justified. Avoid Linux-only syscalls unless a portable fallback is provided (see `cpy.c` for an example using `sendfile` with an `fread`/`fwrite` fallback).
- **Testing**: Provide simple test cases or scripts. Manual testing is encouraged; avoid heavy test frameworks.
- **Documentation**: Inline comments for non-obvious logic only. No external docs unless the code is truly complex (which it shouldn't be).
- **Licensing**: All contributions must be licensed under the same terms as the project (check `LICENSE`).

---

## Current Utilities

These are the existing tools — read their source before writing a new one to understand the expected style:

| Binary  | Source    | Description                                   |
|---------|-----------|-----------------------------------------------|
| `brit`  | `brit.c`  | Write stdin to stdout and a file (like `tee`) |
| `chwn`  | `chwn.c`  | Change file owner and group (names or IDs)    |
| `cnt`   | `cnt.c`   | Count lines, words, bytes (like `wc`)         |
| `cpy`   | `cpy.c`   | Copy a file                                   |
| `cwd`   | `cwd.c`   | Print current working directory (like `pwd`)  |
| `del`   | `del.c`   | Delete file(s); `-r` removes directories      |
| `env`   | `env.c`   | Print environment variables; optional prefix  |
| `hd`    | `hd.c`    | Print first N lines of file (like `head`)     |
| `hn`    | `hn.c`    | Show or set hostname                          |
| `jgrep` | `jgrep.c` | Search for pattern in file or stdin           |
| `lf`    | `lf.c`    | List files in a directory (sorted)            |
| `lnk`   | `lnk.c`   | Create hard or symbolic link                  |
| `mat`   | `mat.c`   | Print file contents (like `cat`)              |
| `mkd`   | `mkd.c`   | Create directory; `-p` creates parents        |
| `move`  | `move.c`  | Move or rename a file                         |
| `perm`  | `perm.c`  | Show file permissions in `rwxrwxrwx` format   |
| `print` | `print.c` | Print a string to stdout (like `echo`)        |
| `spec`  | `spec.c`  | Print file, suppressing adjacent duplicates   |
| `srt`   | `srt.c`   | Sort lines in a file alphabetically           |
| `tch`   | `tch.c`   | Create file or update modification dt         |
| `tl`    | `tl.c`    | Print last N lines of file (like `tail`)      |
| `nap`   | `nap.c`   | Sleep for a specified number of seconds       |
| `dt`    | `dt.c`    | Print current time in human-readable format   |
| `wm`    | `wm.c`    | Print current user name (like `whoami`)       |

---

## How to Contribute

1. **Fork and Clone**: Fork the repository, clone it locally, and create a feature branch for your changes.
2. **Understand the Codebase**: Review existing utilities (e.g., `cnt.c` for multi-file handling, `del.c` for recursion, `cpy.c` for fallback strategies) to see examples of compliant code.
3. **Make Changes**:
   - Ensure your code follows the size and header limits.
   - Run `make` to build and test (check `Makefile` for build instructions).
   - Verify with `gcc -Wall -Wextra` — zero warnings required.
   - Check for memory issues with `valgrind` if available.
4. **Update the Makefile**: Add your utility to the `all`, `clean`, and `install` targets.
5. **Update README.md**: Add your utility to the appropriate table with its usage and description.
6. **Submit a Pull Request**:
   - Describe the change: What problem does it solve? How does it align with UNIX/suckless principles?
   - Reference any related issues.
7. **Review Process**: Maintainers will check for compliance with principles, size limits, and quality. Be prepared to refactor if needed.

---

## Examples of Compliant Code

**Simple utility — `cwd.c`** (print working directory, 8 lines):
```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void) {
    char *cwd = getcwd(NULL, 0);
    if (!cwd) { perror("FATAL ERROR"); return 1; }
    printf("%s\n", cwd);
    free(cwd);
    return 0;
}
```

**Utility with helper function — `cnt.c`** (count lines/words/bytes): the `count()` helper is under 10 lines; `main` is under 20 lines. The two together stay well within the 100-line limit.

Avoid adding features like progress bars, colour output, or interactive modes — these violate "do one thing well."

---

## Common Pitfalls to Avoid
- **Bloat**: Don't add optional features or configurations. If it's not core, it doesn't belong.
- **Dependencies**: No external libs (e.g., no libcurl). libc only.
- **Over-Abstraction**: Use plain C — no OOP, generics, or macros unless they genuinely simplify.
- **Ignoring Limits**: If your code exceeds 100 lines per function or 5 headers, split it or simplify. No exceptions without maintainer approval.
- **Unchecked allocations**: Every `malloc`, `realloc`, and `strdup` must have its return value checked.
- **Wrong output stream**: Usage/error messages go to `stderr`, normal output goes to `stdout`.
- **Reserved identifiers**: Don't redefine standard macros like `BUFSIZ`, `EOF`, or `NULL`.

---

## Resources
- [UNIX Philosophy](https://en.wikipedia.org/wiki/Unix_philosophy)
- [Suckless Philosophy](https://suckless.org/philosophy/)
- [K&R C Style](https://en.wikipedia.org/wiki/Indentation_style#K&R_style)
- [README.md](README.md) — full utility reference with usage examples

Thank you for contributing! Let's keep **The-JLC-Project** simple and effective.

