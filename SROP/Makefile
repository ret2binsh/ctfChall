TARGET = prog
CC = nasm
CFLAGS = -f elf64
LD = ld
PROG = SROP.asm
OBJECT = SROP.o

default: $(TARGET)
all: default

$(OBJECT):
	$(CC) $(CFLAGS) $(PROG)

$(TARGET): $(OBJECT)
	$(LD) $(OBJECT) -o $@

clean:
	rm -f *.o
	rm -f $(TARGET)
