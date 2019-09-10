#include <stdio.h>
#include <stdlib.h>

#define BUFFER 64

void gimme_flag(){

	FILE *f;
	char c;

	f = fopen("flag.txt","r");
	while ((c = fgetc(f)) != EOF){
		printf("%c%",c);
	}
	fclose(f);
}

int main(){

	char input[BUFFER];

	printf("Enter the password: ");
	fflush(stdout);
	gets(input);

	return 0;
}
