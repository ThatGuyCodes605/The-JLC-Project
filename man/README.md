# Man Pages for The JLC Project

This directory contains man pages for all utilities in The JLC Project.

## Available Man Pages

- `brit.1` - Write stdin to stdout and a file
- `chwn.1` - Change file owner and group
- `cnt.1` - Count lines, words, and bytes
- `cpy.1` - Copy files
- `duct.1` - Print machine architecture
- `dt.1` - Print current date and time
- `del.1` - Delete files and directories
- `env.1` - Print environment variables
- `hd.1` - Print first lines of files
- `hn.1` - Print or set hostname
- `jfetch.1` - Display system information with ASCII art
- `jsh` - A simple, minimal, and interactive shell
- `jgrep.1` - Search for patterns in files
- `lf.1` - List files
- `lnk.1` - Create links
- `mat.1` - Print file contents
- `mkd.1` - Create directories
- `move.1` - Move/rename files
- `nap.1` - Sleep for specified seconds
- `perm.1` - Show file permissions
- `print.1` - Print text
- `short.1` - Sort lines in a file (optimized)
- `sim.1` - Print infinite "y" strings
- `spec.1` - Suppress duplicate adjacent lines
- `srt.1` - Sort lines in a file
- `tch.1` - Create or update file timestamps
- `tl.1` - Print last lines of files
- `whoisdat.1` - Print current user
- `wm.1` - Print current user

## Installation

To install the man pages, run:

```
sudo make install
```

This will copy all executables and man pages to the appropriate system directories.

## Viewing Man Pages

After installation, you can view man pages using:

```
man chwn
man cpy
man jgrep
# etc.
```

## Manual Installation

If you want to install only the man pages:

```
sudo make manpages
```

Or manually copy them:

```
sudo cp man/man1/*.1 /usr/share/man/man1/
sudo mandb
```
