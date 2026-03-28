# Default compiler (can be overridden with make CC=compiler)
CC ?= gcc
# Optimized flags for performance
CFLAGS = -O3 -flto -DNDEBUG -Wall -Wextra
MANDIR = man/man1

BINDIR = /usr/bin

BINS = mat jgrep move cpy print lf perm spec srt hn chwn brit cnt hd tl tch mkd del lnk cwd env nap dt wm J whoisdat sim short duct

MANS = man/man1/brit.1 man/man1/chwn.1 man/man1/cnt.1 man/man1/cpy.1 \
       man/man1/cwd.1 man/man1/del.1 man/man1/dt.1 man/man1/env.1 \
       man/man1/hd.1 man/man1/hn.1 man/man1/jgrep.1 man/man1/J.1 \
       man/man1/lf.1 man/man1/lnk.1 man/man1/mat.1 man/man1/mkd.1 \
       man/man1/move.1 man/man1/nap.1 man/man1/perm.1 man/man1/print.1 \
       man/man1/spec.1 man/man1/srt.1 man/man1/tch.1 man/man1/tl.1 \
       man/man1/whoisdat.1 man/man1/wm.1 man/man1/sim.1

all: $(BINS)

mat: mat.c
	$(CC) $(CFLAGS) mat.c -o mat

jgrep: jgrep.c
	$(CC) $(CFLAGS) jgrep.c -o jgrep

move: move.c
	$(CC) $(CFLAGS) move.c -o move

cpy: cpy.c
	$(CC) $(CFLAGS) cpy.c -o cpy

print: print.c
	$(CC) $(CFLAGS) print.c -o print

lf: lf.c
	$(CC) $(CFLAGS) lf.c -o lf

perm: perm.c
	$(CC) $(CFLAGS) perm.c -o perm

spec: spec.c
	$(CC) $(CFLAGS) spec.c -o spec

srt: srt.c
	$(CC) $(CFLAGS) srt.c -o srt

hn: hn.c
	$(CC) $(CFLAGS) hn.c -o hn

chwn: chwn.c
	$(CC) $(CFLAGS) chwn.c -o chwn

brit: brit.c
	$(CC) $(CFLAGS) brit.c -o brit

cnt: cnt.c
	$(CC) $(CFLAGS) cnt.c -o cnt

hd: hd.c
	$(CC) $(CFLAGS) hd.c -o hd

tl: tl.c
	$(CC) $(CFLAGS) tl.c -o tl

tch: tch.c
	$(CC) $(CFLAGS) tch.c -o tch

mkd: mkd.c
	$(CC) $(CFLAGS) mkd.c -o mkd

del: del.c
	$(CC) $(CFLAGS) del.c -o del

lnk: lnk.c
	$(CC) $(CFLAGS) lnk.c -o lnk

cwd: cwd.c
	$(CC) $(CFLAGS) cwd.c -o cwd

env: env.c
	$(CC) $(CFLAGS) env.c -o env

nap: nap.c
	$(CC) $(CFLAGS) nap.c -o nap

dt: dt.c
	$(CC) $(CFLAGS) dt.c -o dt

wm: wm.c
	$(CC) $(CFLAGS) wm.c -o wm

J: J.c
	$(CC) $(CFLAGS) J.c -o J

whoisdat: whoisdat.c
	$(CC) $(CFLAGS) whoisdat.c -o whoisdat

sim: sim.c
	$(CC) $(CFLAGS) sim.c -o sim

short: short.c
	$(CC) $(CFLAGS) short.c -o short

duct: duct.c
	$(CC) $(CFLAGS) duct.c -o duct

clean:
	rm -f $(BINS)

# Detect OS
UNAME_S := $(shell uname -s)

# Platform-specific installation commands
ifeq ($(UNAME_S),Linux)
	INSTALL_BIN = install -m 755
	INSTALL_MAN = install -m 644
	MKDIR = install -d
elifneq ($(findstring CYGWIN,$(UNAME_S)),)
	INSTALL_BIN = install -m 755
	INSTALL_MAN = install -m 644
	MKDIR = install -d
else
	# Default (Darwin/FreeBSD/others) - use cp and chmod
	INSTALL_BIN = cp
	INSTALL_MAN = cp
	MKDIR = mkdir -p
endif

install: all
	$(MKDIR) $(BINDIR) $(MANDIR)
	@for bin in $(BINS); do \
		if [ -f "$$bin" ]; then \
			$(INSTALL_BIN) "$$bin" "$(BINDIR)/"; \
		fi \
	done
	@for man in $(MANS); do \
		if [ -f "$$man" ]; then \
			$(INSTALL_MAN) "$$man" "$(MANDIR)/"; \
		fi \
	done
	-mandb -q

uninstall:
	cd $(BINDIR) && rm -f $(BINS)
	cd $(MANDIR) && rm -f $(notdir $(MANS))
	-mandb -q