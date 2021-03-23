#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

void flag()
{
	int fd;
	fd = open("flag.txt", O_RDONLY);
	char c;
	while (read(fd, &c, 1))
		printf("%c",c);
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


