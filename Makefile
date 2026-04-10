# Compiler settings (can be overridden when calling make)
CC ?= gcc
CFLAGS ?= -Wall -Wextra

# Install directories (can be overridden)
BINDIR ?= /usr/local/bin
MANDIR ?= /usr/local/share/man/man1

# Programs to build
BINS = mat jgrep move cpy print lf perm spec srt hn chwn brit cnt hd tl tch mkd del lnk cwd env nap dt duct wm whoisdat short sim jfetch

# Manual pages
MANS = man/man1/brit.1 man/man1/chwn.1 man/man1/cnt.1 man/man1/cpy.1 \
       man/man1/cwd.1 man/man1/del.1 man/man1/dt.1 man/man1/env.1 \
       man/man1/hd.1 man/man1/hn.1 man/man1/jfetch.1 man/man1/jgrep.1 man/man1/lf.1 \
       man/man1/lnk.1 man/man1/mat.1 man/man1/mkd.1 man/man1/move.1 \
       man/man1/nap.1 man/man1/perm.1 man/man1/print.1 man/man1/spec.1 \
       man/man1/srt.1 man/man1/tch.1 man/man1/tl.1

# Default target
all: $(BINS)

# Build rule for any C program
%: %.c
	$(CC) $(CFLAGS) $< -o $@

# Installation
install: all
	@echo "Installing binaries to $(BINDIR) and man pages to $(MANDIR)"
	install -d "$(BINDIR)" "$(MANDIR)"
	install -m 755 $(BINS) "$(BINDIR)/"
	@for man in $(MANS); do \
		if [ -f "$$man" ]; then \
			install -m 644 "$$man" "$(MANDIR)/"; \
		fi \
	done

# Uninstall
uninstall:
	@echo "Removing binaries and man pages"
	-rm -f $(BINDIR)/$(BINS)
	-rm -f $(addprefix $(MANDIR)/, $(notdir $(MANS)))

# Clean build artifacts
clean:
	rm -f $(BINS)
