CC = gcc
CFLAGS = -Wall -Wextra

all: mat jgrep move cpy print lf perm spec srt hn chwn brit cnt hd tl tch mkd del lnk cwd env nap dt wm

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

clean:
	rm -f mat jgrep move cpy print lf perm spec srt hn chwn brit cnt hd tl tch mkd del lnk cwd env nap dt wm

install: all
	sudo cp mat jgrep move cpy print lf perm spec srt hn chwn brit cnt hd tl tch mkd del lnk cwd env nap dt wm /usr/bin/
