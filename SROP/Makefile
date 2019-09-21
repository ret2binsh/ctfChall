CC      = gcc
CFLAGS  = -s
RM      = rm -f
PROG    = srop.c
OUT     = prog

default: all

all: Build

Build: srop.c
	$(CC) $(CFLAGS) -o srop.s -c $(PROG)

clean:
	$(RM) prog srop.s
