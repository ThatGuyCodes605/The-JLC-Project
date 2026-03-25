# Man Pages for The JLC Project

This directory contains man pages for all utilities in The JLC Project.

## Available Man Pages

- `chwn.1` - Change file owner and group
- `cpy.1` - Copy files
- `jgrep.1` - Search for patterns in files
- `lf.1` - List files
- `mat.1` - Print file contents
- `move.1` - Move/rename files
- `perm.1` - Show file permissions
- `print.1` - Print text
- `spec.1` - Show file information
- `srt.1` - Sort lines in a file

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