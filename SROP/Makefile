TARGET = prog
CC = nasm
CFLAGS = -f bin
PROG = SROP.asm

default: $(TARGET)
all: default

$(TARGET):
	$(CC) $(CFLAGS) -o $(TARGET) $(PROG) && chmod +x $(TARGET)

clean:
	rm -f *.o
	rm -f $(TARGET)
