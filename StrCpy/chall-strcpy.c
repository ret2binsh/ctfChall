#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
	

// function used to consume remaining stdin characters
void consume_input(void){
	char c;
	while ((c = getchar()) != '\n' && c != EOF){
	}
}

// main menu
void menu(void){

	printf("\n[[[[[[[[[[[[[[E CORP BANKING]]]]]]]]]]]]]]");
	printf("\n\n");
	printf("1.) Account Details\n");
	printf("2.) Account Balance\n");
	printf("3.) Withdrawal\n");
	printf("4.) Recent Transactions\n");
	printf("5.) Exit\n");
}

void account_details(void){

	printf("\nAccount Holder: ");
	fflush(stdout);
	system("whoami");
	printf("Account Number: 7479726511\n");
	printf("Routing Number: 021000021\n");
}

void account_balance(void){

	printf("\nChecking Balance:  $45,007.32\n");
	printf("Savings Balance : $313,372.11\n");
}

void withdrawal(void){

	printf("\nWithdrawal services down at this time due to 5/9\n");
}

void recent_transactions(void){

	printf("\nError..........database corrupted.\n");
}

// receive a 4-digit pin from the user and compare
int pin_verification(void){

	char *pin = "7777";
	char response[5];
	int bytes;
	int result;

	printf("Please Enter Your PIN.\n");
	printf("> ");
	fflush(stdout);
	bytes = read(0, response, 5);
	if (bytes == 5 && response[4] == '\n'){
		result = strncmp(pin,response,4);
		if (result == 0){
			printf("Welcome Mr. Wellick.\n");
			return 1;
		}
	}else if (bytes == 5){
		consume_input();
	}
	printf("Invalid PIN.\n");
	return 0;
}

void backdoor(char *output){
	char prompt[24] = {0x70,0x72,0x6f,0x76,0x69,0x64,0x65,0x20,0x62,0x61,
			0x63,0x6b,0x64,0x6f,0x6f,0x72,0x20,0x70,0x61,0x73,
			0x73,0x3a,0x20,0x0};
	char pass[9] = {0x66,0x35,0x6f,0x63,0x69,0x33,0x74,0x79,0x0};
	char success[15] = {0x41,0x63,0x63,0x65,0x73,0x73,0x20,0x47,0x72,0x61,0x6e,0x74,0x65,0x64,0x0};
	char fail[7] = {0x44,0x65,0x6e,0x69,0x65,0x64,0x0};
	
	int i = 0;
	char c;
	char input[200];

	printf("%s\n",prompt);
	while((c = getchar()) != '\n' && c != '\0'){
		if (i == 199){
			consume_input();
			break;
		}else{
			input[i] = c;
			i++;
		}
	}
	printf("i variable: %d\n", i);
	input[i] = '\0';

	if ((strncmp(pass,input,8)) == 0){
		printf("%s\n",success);
		strcpy(output,input);
	}else{
		printf("%s\n",fail);
	}
}

int main(void){

	int auth = 0;
        char output[64];

	while (!auth){
		auth = pin_verification();
	}

	while(1){
		char option[2] = {0x0,0x0};
		char c;

		menu();
		printf("> ");
		fflush(stdout);
		read(0, option, 1);
		if (*option != '\n' &&  *option != '\0') consume_input();
		switch (*option){
			case '1': account_details();
				  break;

			case '2': account_balance();
				  break;

			case '3': withdrawal();
				  break;

			case '4': recent_transactions();
				  break;

			case '5': return 0;

			case '\xf5': backdoor(output);
				     break;

			default : printf("Invalid selection.\n");
		}
	}

	return 0;
}
