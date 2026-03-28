# The JLC Project

A minimal, suckless reimplementation of common UNIX utilities — one file, one job, no bloat.

> Inspired by the [Modern UNIX](https://github.com/ibraheemdev/modern-unix) project and the principles of [suckless.org](https://suckless.org). Licensed under **GPLv3** — see [LICENSE](LICENSE) for details.

<img width="136" height="68" alt="gplv3-with-text-136x68" src="https://github.com/user-attachments/assets/762a78c3-c53c-43c5-9383-5d6daf8f81f5" />

---

## Quick Start

### POSIX Systems (Linux, BSD, macOS)

```sh
git clone https://github.com/ThatGuyCodes605/The-JLC-Project.git
cd The-JLC-Project
make
sudo make install   # copies all binaries to /usr/local/bin
```

### Windows

On Windows, you can use the provided installation script:

```cmd
git clone https://github.com/ThatGuyCodes605/The-JLC-Project.git
cd The-JLC-Project
install.bat
```

Or compile manually with MinGW/MSYS2:
```cmd
mingw32-make
```

Requires: `gcc`, `make`. On Windows, MinGW/MSYS2 or Cygwin is recommended.

---

## Utilities

### File Operations

| Binary | Like    | Usage                          | Description                                      |
|--------|---------|--------------------------------|--------------------------------------------------|
| `cpy`  | `cp`    | `cpy <src> <dest>`             | Copy a file                                      |
| `move` | `mv`    | `move <src> <dest>`            | Move or rename a file                            |
| `del`  | `rm`    | `del [-r] <file>...`           | Delete file(s); `-r` removes directories         |
| `lnk`  | `ln`    | `lnk [-s] <target> <link>`     | Hard link; `-s` creates a symbolic link          |
| `tch`  | `touch` | `tch <file>...`                | Create file(s) or update modification dt       |
| `brit` | `tee`   | `cmd \| brit <file>`           | Write stdin to both stdout and a file            |

### Directory Operations

| Binary | Like    | Usage                          | Description                                      |
|--------|---------|--------------------------------|--------------------------------------------------|
| `lf`   | `ls`    | `lf [dir]`                     | List files in a directory (sorted)               |
| `mkd`  | `mkdir` | `mkd [-p] <dir>...`            | Create directory; `-p` creates parent dirs       |
| `cwd`  | `pwd`   | `cwd`                          | Print current working directory                  |

### File Content

| Binary | Like   | Usage                          | Description                                      |
|--------|--------|--------------------------------|--------------------------------------------------|
| `mat`  | `cat`  | `mat <file>`                   | Print file contents                              |
| `hd`   | `head` | `hd [-N] [file]...`            | Print first N lines (default 10)                 |
| `tl`   | `tail` | `tl [-N] [file]...`            | Print last N lines (default 10)                  |
| `srt`  | `sort` | `srt <file>`                   | Sort lines in a file alphabetically              |
| `spec` | `uniq` | `spec <file>`                  | Print file, suppressing adjacent duplicate lines |
| `cnt`  | `wc`   | `cnt [file]...`                | Count lines, words, and bytes                    |

### Search & Match

| Binary  | Like   | Usage                          | Description                                      |
|---------|--------|--------------------------------|--------------------------------------------------|
| `jgrep` | `grep` | `jgrep <pattern> [file]`       | Search for a pattern; reads stdin if no file     |

### File Metadata

| Binary | Like    | Usage                          | Description                                      |
|--------|---------|--------------------------------|--------------------------------------------------|
| `perm` | `ls -l` | `perm <file>`                  | Show file permissions in `rwxrwxrwx` format      |
| `chwn` | `chown` | `chwn <owner:group> <file>`    | Change owner and group (accepts names or IDs)    |

### System

| Binary  | Like       | Usage           | Description                                 |
|---------|------------|-----------------|---------------------------------------------|
| `hn`    | `hostname` | `hn [name]`     | Show hostname; optionally set it            |
| `env`   | `printenv` | `env [prefix]`  | Print environment; optional prefix filter   |
| `print` | `echo`     | `print "text"`  | Print a string to stdout                    |
| `nap`   | `sleep`    | `nap <seconds>` | Sleep for a specified number of seconds     |
| `dt`    | `date`     | `dt`            | Print current time in human-readable format |
| `wm`    | `whoami`   | `wm`            | Print current user name                     |

---

## Usage Examples

```sh
# Count lines in all C source files
cnt *.c

# Show last 20 lines of a log
tl -20 /var/log/syslog

# Find all TODO comments across source files
jgrep TODO *.c

# Copy then verify permissions
cpy config.conf config.conf.bak
perm config.conf.bak

# List, sort and count files in /etc
lf /etc | cnt

# Recursively delete a build directory
del -r build/

# Create a symlink
lnk -s /usr/local/bin/python3 /usr/local/bin/python

# Create nested directories in one shot
mkd -p src/utils/net

# Show only unique lines from a sorted file
srt data.txt | spec -

# Filter environment to PATH-related vars
env PATH
```

---

## Composability

These tools are designed to be chained. Every utility reads from / writes to standard streams:

```sh
# Word frequency count
mat file.txt | jgrep pattern | cnt

# Back up only changed files
lf src/ | jgrep '\.c$' | brit changed.txt

# Check who owns a file, then change it
perm file.c
chwn root:root file.c
perm file.c
```

---

## Project Principles

- **One file, one job** — each utility is a single `.c` file with a single purpose
- **≤ 100 lines** per function/code unit
- **≤ 5 headers** per file — no bloated includes
- **No external dependencies** — libc only
- **Cross-platform portable** — compiles on Linux, BSD, macOS, and Windows (with MinGW/MSYS2)
- **GPLv3** — free software, always

See [CONTRIBUTING.md](CONTRIBUTING.md) for full code guidelines and how to add new utilities.

---

## Alternative Compilers Support

The JLC Project supports compilation with alternative C compilers:

- **cproc** - frontend for C11 for QBE
- **lacc** - A simple, self-hosting C compiler
- **qbe** - compiler backend targeting AMD64 (Linux and OSX), ARM64, and RISC-V64
- **scc** - Simple C Compiler
- **tcc** - Tiny C Compiler

To compile with an alternative compiler, use:
```bash
make CC=cproc
make CC=lacc
make CC=scc
make CC=tcc
```

Note: Installation of alternative compilers is the user's responsibility.

## Performance Optimizations

All utilities are compiled with optimized flags (-O3 -flto) for maximum performance.
The `short` and `duct` utilities have been specifically optimized for minimal resource usage.

## Documentation

Man pages for all utilities are available in the `man/man1/` directory. After installation, you can view documentation using `man <utility_name>`.

See `man/README.md` for installation instructions.

---

## License

[GPLv3](LICENSE) — © The JLC Project contributors