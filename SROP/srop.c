#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define BINSH "/bin/sh"


int main(void){

	char buf[32];

	read(0, buf, 200);

	return 0;
}
