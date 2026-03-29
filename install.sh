#!/bin/sh

# Cross-platform installer for The JLC Project
# Follows suckless principles: simple, portable, no bloat

# Detect OS
OS="$(uname -s)"

# Default installation directories
PREFIX="${PREFIX:-/usr/local}"
BINDIR="${BINDIR:-$PREFIX/bin}"
MANDIR="${MANDIR:-$PREFIX/share/man}"

# Help message
usage() {
    echo "Usage: $0 [OPTIONS]"
    echo "Install The JLC Project utilities"
    echo ""
    echo "Options:"
    echo "  -p PREFIX    Install prefix (default: /usr/local)"
    echo "  -b BINDIR    Binary directory (default: PREFIX/bin)"
    echo "  -m MANDIR    Man page directory (default: PREFIX/share/man)"
    echo "  -h           Show this help message"
    echo ""
    echo "Examples:"
    echo "  $0                    # Install to /usr/local"
    echo "  $0 -p /opt/jlc        # Install to /opt/jlc"
    echo "  $0 -b ~/bin           # Install binaries to ~/bin"
}

# Parse command line arguments
while getopts "p:b:m:h" opt; do
    case $opt in
        p) PREFIX="$OPTARG" ;;
        b) BINDIR="$OPTARG" ;;
        m) MANDIR="$OPTARG" ;;
        h) usage; exit 0 ;;
        *) usage; exit 1 ;;
    esac
done

# Compile all utilities
echo "Compiling utilities..."
make clean >/dev/null 2>&1
if ! make 2>/dev/null; then
    echo "ERROR: Compilation failed. Please check that gcc and make are installed."
    exit 1
fi

# Create directories
echo "Creating directories..."
mkdir -p "$BINDIR" || { echo "ERROR: Failed to create $BINDIR"; exit 1; }
mkdir -p "$MANDIR/man1" || { echo "ERROR: Failed to create $MANDIR/man1"; exit 1; }

# Install binaries
echo "Installing binaries to $BINDIR..."
for bin in mat jgrep move cpy print lf perm spec srt hn chwn brit cnt hd tl tch mkd del lnk cwd env nap dt wm J whoisdat sim short duct; do
    if [ -f "$bin" ]; then
        cp "$bin" "$BINDIR/" || { echo "ERROR: Failed to copy $bin"; exit 1; }
        chmod 755 "$BINDIR/$bin" || { echo "ERROR: Failed to set permissions on $bin"; exit 1; }
    fi
done

# Install man pages
echo "Installing man pages to $MANDIR/man1..."
for manpage in man/man1/*.1; do
    if [ -f "$manpage" ]; then
        cp "$manpage" "$MANDIR/man1/" || { echo "ERROR: Failed to copy $manpage"; exit 1; }
        chmod 644 "$MANDIR/man1/$(basename "$manpage")" || { echo "ERROR: Failed to set permissions on $manpage"; exit 1; }
    fi
done

# Update man database if available
echo "Updating man database..."
mandb -q >/dev/null 2>&1 || true

echo "Installation complete!"
echo "Binaries installed to: $BINDIR"
echo "Man pages installed to: $MANDIR/man1"
echo ""
echo "You can now use the JLC utilities. Try 'mat --help' to get started."