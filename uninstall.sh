#!/bin/sh

# Cross-platform uninstaller for The JLC Project
# Follows suckless principles: simple, portable, no bloat

# Default installation directories
PREFIX="${PREFIX:-/usr/local}"
BINDIR="${BINDIR:-$PREFIX/bin}"
MANDIR="${MANDIR:-$PREFIX/share/man}"

# Help message
usage() {
    echo "Usage: $0 [OPTIONS]"
    echo "Uninstall The JLC Project utilities"
    echo ""
    echo "Options:"
    echo "  -p PREFIX    Install prefix (default: /usr/local)"
    echo "  -b BINDIR    Binary directory (default: PREFIX/bin)"
    echo "  -m MANDIR    Man page directory (default: PREFIX/share/man)"
    echo "  -h           Show this help message"
    echo ""
    echo "Examples:"
    echo "  $0                    # Uninstall from /usr/local"
    echo "  $0 -p /opt/jlc        # Uninstall from /opt/jlc"
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

# Remove binaries
echo "Removing binaries from $BINDIR..."
for bin in mat jgrep move cpy print lf perm spec srt hn chwn brit cnt hd tl tch mkd del lnk cwd env nap dt wm J whoisdat sim short duct; do
    if [ -f "$BINDIR/$bin" ]; then
        rm -f "$BINDIR/$bin"
    fi
done

# Remove man pages
echo "Removing man pages from $MANDIR/man1..."
for manpage in man/man1/*.1; do
    if [ -f "$manpage" ]; then
        rm -f "$MANDIR/man1/$(basename "$manpage")"
    fi
done

# Update man database if available
echo "Updating man database..."
mandb -q >/dev/null 2>&1 || true

echo "Uninstallation complete!"