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

## Code Guidelines

### Size Constraints
- **Maximum lines per code piece**: Every function, module, or standalone code unit must be **50 lines or fewer**. This enforces focus and readability. Break larger logic into smaller, composable functions.
- "Code piece" refers to individual functions or small modules (e.g., a single utility's main logic). Entire files can be longer if they contain multiple small pieces, but each piece must adhere to the limit.
- **Exceptions**: Comments, blank lines, and preprocessor directives (e.g., `#include`) do not count toward the line limit.
- **Rationale**: Large functions are harder to understand, test, and maintain. This rule promotes the UNIX principle and suckless minimalism.

### Header Files
- **Maximum header files per utility**: Each utility (e.g., a single `.c` file and its dependencies) must include **5 header files or fewer**.
- This includes standard library headers (e.g., `<stdio.h>`, `<stdlib.h>`) and any custom headers.
- Avoid pulling in unnecessary headers—only include what's essential for the task.
- **Rationale**: Excessive includes lead to bloated binaries and slower compilation. It also encourages self-sufficiency and reduces dependencies.

### General Coding Standards
- **Language**: C (standard C99 or later for portability).
- **Style**: Follow K&R style (as in the Linux kernel or suckless projects). Use tabs for indentation, no trailing whitespace, and consistent naming (`snake_case` for variables/functions).
- **Error Handling**: Use simple, explicit checks. Avoid exceptions or complex error propagation—return codes or `errno` suffice.
- **Memory Management**: Manual allocation/deallocation only. No garbage collection or smart pointers. Free resources promptly to prevent leaks.
- **Portability**: Code must compile on POSIX systems (Linux, BSD, etc.) without platform-specific extensions unless justified.
- **Testing**: Provide simple test cases or scripts. Manual testing is encouraged; avoid heavy test frameworks.
- **Documentation**: Inline comments for non-obvious logic. No external docs unless the code is truly complex (which it shouldn't be).
- **Licensing**: All contributions must be licensed under the same terms as the project (check `LICENSE`).

## How to Contribute

1. **Fork and Clone**: Fork the repository, clone it locally, and create a feature branch for your changes.
2. **Understand the Codebase**: Review existing utilities (e.g., `cpy.c`, `jgrep.c`) to see examples of compliant code. Each tool is small, focused, and adheres to the rules.
3. **Make Changes**:
   - Ensure your code follows the size and header limits.
   - Run `make` to build and test (check `Makefile` for build instructions).
   - Verify with tools like `valgrind` for memory issues or `gcc -Wall -Wextra` for warnings.
4. **Submit a Pull Request**:
   - Describe the change briefly: What problem does it solve? How does it align with UNIX/suckless principles?
   - Reference any related issues.
   - Ensure CI passes (if configured).
5. **Review Process**: Maintainers will check for compliance with principles, size limits, and quality. Be prepared to refactor if needed.

## Examples of Compliant Code
A utility like `cpy.c` (file copying) should be under 50 lines, include only essentials like `<stdio.h>` and `<stdlib.h>`, and do nothing but copy files efficiently.

Avoid adding features like progress bars or GUI wrappers—these violate "do one thing well."

## Common Pitfalls to Avoid
- **Bloat**: Don't add optional features or configurations. If it's not core, it doesn't belong.
- **Dependencies**: No external libs (e.g., no libcurl for networking unless the tool is purely for that).
- **Over-Abstraction**: Use plain C—no OOP, generics, or macros unless they simplify without adding complexity.
- **Ignoring Limits**: If your code exceeds 50 lines or 5 headers, split it or simplify. No exceptions without maintainer approval.

## Resources
- [UNIX Philosophy](https://en.wikipedia.org/wiki/Unix_philosophy)
- [Suckless Philosophy](https://suckless.org/philosophy/)
- [K&R C Style](https://en.wikipedia.org/wiki/Indentation_style#K&R_style)

Thank you for contributing! Let's keep **The-JLC-Project** simple and effective.
