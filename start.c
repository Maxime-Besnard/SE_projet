#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
	int pid;
	int pid2;
	int pid3;
	int pid4;
	
	char* num = "0001000000000000";
	char* num2 = "0001000111000001";
	char* num3 = "0001000000000001";
	
	char* val = "6";
	char* val2 = "10";
	char* val3 = "12";
	
	printf("\nTest du projet avec un test valide\n\n");
	
	pid = fork();
	if(pid == 0){

		execlp("./acquisition","./acquisition",num,val,NULL);
		printf("erreur\n");
		perror("exec");
		exit(EXIT_FAILURE);
	}
	
	wait(NULL);
	
	printf("\n\n\nTest du projet avec un autre test valide\n\n");
	
	pid2 = fork();
	if(pid2 == 0){

		execlp("./acquisition","./acquisition",num2,val2,NULL);
		printf("erreur\n");
		perror("exec");
		exit(EXIT_FAILURE);
	}
	
	wait(NULL);
	
	printf("\n\n\nTest du projet avec un test non répertorié\n\n");
	
	pid3 = fork();
	if(pid3 == 0){

		execlp("./acquisition","./acquisition",num3,val,NULL);
		printf("erreur\n");
		perror("exec");
		exit(EXIT_FAILURE);
	}
	
	wait(NULL);
	
	printf("\n\n\nTest du projet avec un test périmé\n\n");
	
	pid = fork();
	if(pid == 0){

		execlp("./acquisition","./acquisition",num,val3,NULL);
		printf("erreur\n");
		perror("exec");
		exit(EXIT_FAILURE);
	}
	
	wait(NULL);
	
	return 0;
}