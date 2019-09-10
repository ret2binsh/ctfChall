#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#define USER_MAX 32
#define TEAM_MAX 28

struct ctfuser{
	char name[USER_MAX];
	char pass[USER_MAX];
};

struct ctfteam{
	char name[TEAM_MAX];
	char pass[TEAM_MAX];
	int team_num;
};

void clear_buffer(){

	char c;
	while ((c = getchar()) != '\n' && c != EOF){
	}
}

void menu(){
	printf("**********************\n");
	printf("1.) CTF User Login\n");
	printf("2.) CTF Team Login\n");
	printf("3.) Display Team\n");
	printf("4.) Delete Team\n");
	printf("5.) Print Flag\n");
	printf("6.) Exit\n\n");
}

struct ctfuser * get_user(struct ctfuser *user){

	return user;
}

struct ctfteam * get_team(struct ctfteam *team){

	return team;
}

void display_team(struct ctfteam *team){

	if (team != NULL){
		printf("Team: %s\n", team->name);
		printf("Team Number: %d\n", team->team_num);
	}else{
		printf("Team not set.\n");
	}
	sleep(1.5);
}

void delete_team(struct ctfteam *team){

	if (team != NULL){
		printf("Deleting team: %s\n", team->name);
		free(team);
	}else{
		printf("Team not set.\n");
	}
	sleep(1.5);
}

void print_flag(struct ctfteam *team){

	if (team != NULL && team->team_num == 0x67616c66){

		FILE *f;
		char c;

		f = fopen("flag.txt","r");

		while((c = fgetc(f)) != EOF){
			printf("%c",c);
		}

		fclose(f);
		exit(0);
	}else{
		printf("You do not have permission to access the flag.\n");
		sleep(1);
	}
}

int main(){

	struct ctfuser *ctf_user = NULL;
	struct ctfteam *ctf_team = NULL;

	char selection[8];

	printf("\e[1;1H\e[2J");
	menu();

	while(1){

		printf("> ");
		fflush(stdout);
		read(0, selection, 1);
		if (*selection != '\n') clear_buffer();
		switch (*selection){

			case '1': get_user(ctf_user);
				  break;
			
			case '2': get_team(ctf_team);
				  break;

			case '3': display_team(ctf_team);
				  break;

			case '4': delete_team(ctf_team);
				  break;

			case '5': print_flag(ctf_team);
				  break;

			case '6': printf("Exiting....\n");
				  return 0;

			default : printf("Invalid selection.\n");
				  sleep(.5);
		}

		printf("\e[1;1H\e[2J");
		menu();

	}

	return 0;
}




		


