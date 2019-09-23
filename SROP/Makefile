TARGET = prog
CC = nasm
CFLAGS = -f bin
PROG = SROP.asm

default: $(TARGET)
all: default

$(TARGET):
	$(CC) $(CFLAGS) -o $(TARGET) $(PROG)

clean:
	rm -f *.o
	rm -f $(TARGET)
