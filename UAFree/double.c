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
	printf("         Menu\n");
	printf("1.) CTF User Login\n");
	printf("2.) CTF Team Login\n");
	printf("3.) Display Team\n");
	printf("4.) Delete Team\n");
	printf("5.) Print Flag\n");
	printf("6.) Exit\n\n");
}

// receive username and password and return pointer to struct
struct ctfuser * get_user(struct ctfuser *user){

	user = (struct ctfuser *)malloc(sizeof(struct ctfuser));
	int bytes = 0;

	printf("Enter username: ");
	fflush(stdout);
	// ensure we receive null terminate the string and burn the excess input buffer
	bytes = read(0, user->name, USER_MAX);
	if (bytes == USER_MAX && user->name[USER_MAX-1] != '\n'){

		clear_buffer();
		user->name[USER_MAX-1] = '\0';
	}else if (bytes == USER_MAX){

		user->name[USER_MAX-1] = '\0';
	}else{

		user->name[bytes-1] = '\0';
	}

	printf("Password: ");
	fflush(stdout);
	// ensure we receive null terminate the string and burn the excess input buffer
	bytes = read(0, user->pass, USER_MAX);
	if (bytes == USER_MAX && user->pass[USER_MAX-1] != '\n'){

		clear_buffer();
		user->pass[USER_MAX-1] = '\0';
	}else if (bytes == USER_MAX){

		user->pass[USER_MAX-1] = '\0';
	}else{

		user->pass[bytes-1] = '\0';
	}

	printf("\nWelcome %s\n", user->name);

	fflush(stdout);
	sleep(1);

	return user;
}

struct ctfteam * get_team(struct ctfteam *team){

	team = (struct ctfteam *)malloc(sizeof(struct ctfteam));
	int bytes = 0;

	printf("Enter team name: ");
	fflush(stdout);	
	// ensure we receive null terminate the string and burn the excess input buffer
	bytes = read(0, team->name, TEAM_MAX);
	if (bytes == TEAM_MAX && team->name[TEAM_MAX-1] != '\n'){

		clear_buffer();
		team->name[TEAM_MAX-1] = '\0';
	}else if (bytes == TEAM_MAX){

		team->name[TEAM_MAX-1] = '\0';
	}else{

		team->name[bytes-1] = '\0';
	}

	printf("Enter team password: ");
	fflush(stdout);
	// ensure we receive null terminate the string and burn the excess input buffer
	bytes = read(0, team->pass, TEAM_MAX);
	if (bytes == TEAM_MAX && team->pass[TEAM_MAX-1] != '\n'){

		clear_buffer();
		team->pass[TEAM_MAX-1] = '\0';
	}else if (bytes == TEAM_MAX){

		team->pass[TEAM_MAX-1] = '\0';
	}else{

		team->pass[bytes-1] = '\0';
	}
	
	team->team_num = rand() % 200;
	printf("\nLogged in as team: %s\n", team->name);
	printf("Team number: %d\n",team->team_num);

	fflush(stdout);
	sleep(1);

	return team;
}

// display the team name and team number
void display_team(struct ctfteam *team){

	if (team != NULL){
		printf("Team: %s\n", team->name);
		printf("Team Number: %d\n", team->team_num);
	}else{
		printf("Team not set.\n");
	}
	fflush(stdout);
	sleep(1.5);
}

// delete the team struct, req for the use-after-free vuln
void delete_team(struct ctfteam *team){

	if (team != NULL){
		printf("Deleting team: %s\n", team->name);
		free(team);
	}else{
		printf("Team not set.\n");
	}
	fflush(stdout);
	sleep(1.5);
}

// print flag if the user-after-free vuln aligns the string "flag"
// in the team_num integer field
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
		fflush(stdout);
		sleep(1);
	}
}

int main(){

	struct ctfuser *ctf_user = NULL;
	struct ctfteam *ctf_team = NULL;

	char selection[8];
	srand(time(NULL));

	printf("\e[1;1H\e[2J");
	menu();

	while(1){

		printf("> ");
		fflush(stdout);
		read(0, selection, 1);
		if (*selection != '\n') clear_buffer();
		switch (*selection){

			case '1': ctf_user = get_user(ctf_user);
				  break;
			
			case '2': ctf_team = get_team(ctf_team);
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
				  fflush(stdout);
				  sleep(1);
		}

		printf("\e[1;1H\e[2J");
		menu();

	}

	return 0;
}




		


