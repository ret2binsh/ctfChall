CC     = gcc
CFLAGS = -no-pie
IN     = chall.c
OUT    = binary

default:
	$(CC) $(CFLAGS) -o $(OUT) $(IN)
	strip -s $(OUT) -o $(OUT)

clean:
	rm -f $(OUT)
