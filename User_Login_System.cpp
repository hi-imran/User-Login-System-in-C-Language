#include<conio.h>
#include<stdio.h>
#include<windows.h>

#define ENTER 13
#define TAB 9
#define BKSP 8

struct user{
	char fullname[50];
	char email[50];
	char password[50];
	char username[50];
	char phone[50];
};

void takeinInput(char ch[50]){
	fgets(ch,50,stdin);
	ch[strlen(ch)-1] = 0;
}

char generateUserName(char email[50], char username[50]){
	//imran123@gmail.com
	for(int i=0; i<strlen(email); i++){
		if(email[i] == '@') 
			break;
		else
			username[i] = email[i];
	}
}

void takePassword(char pwd[50]){
	int i;
	char ch;
	while(1){
		ch = getch();
		
		if(ch == ENTER || ch == TAB){
			pwd[i] = '\0';
			break;
		}
		
		else if(ch == BKSP){
			if(i>0){
				i--;
				printf("\b \b");
			}
		}
		
		else{
			pwd[i++] = ch;
			printf("* \b");
			
		}
		
	}
}

int main(){
	system("color 0b");
	FILE *fp;
	struct user user;
	
	char ConfirmPWD[50];
	
	int opt,usrFound = 0;
	printf("\n\t\t\t\t---------------Welcome to Authentication System---------------");
	printf("\nPlease choose your operation");
	printf("\n1.SingUp");
	printf("\n2.Login");
	printf("\n3.Exit");
	
	printf("\nYour Choice:\t");
	scanf("%d",&opt);
	fgetc(stdin);
	/*The program reads an integer using scanf(), then reads a string using fgets()
	 We can notice that above program prints an extra “Enter a character” followed by an extra new line. 
	This happens because every scanf() leaves a newline character in buffer that is read by next scanf.*/
	
	switch(opt){
		case 1:
			system("cls");
			printf("\nEnter your full name:\t");
			takeinInput(user.fullname);
			printf("Enter your email:\t");
			takeinInput(user.email);
			printf("Enter your contact no.:\t");
			takeinInput(user.phone);
			printf("Enter your password:\t");
			takePassword(user.password);
			//printf("%s",user.password);
			printf("\nConfirm your password:\t");
			takePassword(ConfirmPWD);
			
			if(!strcmp(user.password,ConfirmPWD))
			{
				generateUserName(user.email,user.username);
				//printf("\nYour user name is :\t %s",user.username);
				fp = fopen("User.dat","a+");
				fwrite(&user,sizeof(struct user),1,fp);
				if(fp != 0	) 
					printf("\n\nUser registration success, Your user name is %s",user.username);
				else
					printf("\n Sorry! something went wrong :(");
				fclose(fp);
			}
			else
				printf("\n\nOps! Password not matched. Please enter again.");
				Beep(750,300);
			break;
			
		case 2:
			char username[50], pword[50];
			struct user usr;
			
			printf("\nEnter your username:\t");
			takeinInput(username);
			printf("\nEnter your password:\t");
			takePassword(pword);
			
			fp = fopen("User.dat","r");
			while(fread(&usr,sizeof(struct user),1,fp)){
				if(!strcmp(usr.username,username))
				{
					if(!strcmp(usr.password,pword))
					{
						system("cls");
						printf("\n\t\t\t\t\t\tWelcome %s",usr.fullname);
						printf("\n\n|Full name:\t%s",usr.fullname);
						printf("\n|Email:\t\t%s",usr.email);
						printf("\n|Username:\t%s",usr.username);
						printf("\n|Contact no:\t%s",usr.phone);
					}
					else
					{
						printf("\n\nInvalid Password!");
						Beep(800,300);
					}
					usrFound = 1;
				}
			}
			if(!usrFound)
			{
				printf("\n\nUser is not registered.");
				Beep(800,300);
			}
			fclose(fp);
			break;
			
		case 3:
			printf("\n\t\t Bye Bye:)");
			return 0;
	}
	
	return 0;
	
	
}
