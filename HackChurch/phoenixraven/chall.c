#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

void flag()
{
	int fd;
	int out;
	char flag[64];
	fd = open("flag.txt", O_RDONLY);
	memset(flag, '\0', 64);
	out = read(fd, flag, 63);
	for (int i=0; i<out; i++)
		flag[i] = flag[i] ^ 0x7c;
	printf("%s\n",flag);
	close(fd);
}

int main()
{
	char name[32];
	char reason[512];
	printf("Welcome to the Andrews AFB Visitor Center!\n");
	printf("Please provide your name: ");
	fgets(name, 32, stdin);

	printf("Greetings %s please provide a reason for visiting:",name);
	fgets(reason, 600, stdin);
	printf("This is not a valid reason, goodbye...\n");

	return 0;
}
