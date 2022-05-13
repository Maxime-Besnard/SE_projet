#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>

#include "lectureEcriture.h"
#include "message.h"


int main(int argc, char *argv[]) {

	//Récupération du numéro et de la valeur du test
	char* num = argv[1];
	char* val = argv[2];
	
	
	//Creation de 2 processus childs
	int pid;
	int pid2;

	//Creation des pipes 
	int fd1[2];
	int fd2[2];
	int fd3[2];
	int fd4[2];
	pipe(fd1);
	pipe(fd2);
	pipe(fd3);
	pipe(fd4);

	char wterminal[200];
	char rterminal[200];
	char wvalidation[200];
	char rvalidation[200];
	
	pid = fork();

	if(pid == 0){//Processus terminal

		//Envoie des files descriptors et des informations du test avec execlp (précision des pipes de communication avec terminal)
		snprintf(rterminal,sizeof(rterminal),"%d",fd1[0]);
		snprintf(wterminal,sizeof(wterminal),"%d",fd2[1]);

		execlp("./terminal","./terminal",rterminal,wterminal,num,val,NULL);
		printf("erreur\n");
		perror("exec");
		exit(EXIT_FAILURE);
	}
	
	pid2 = fork();
		
	if(pid2 == 0){//Processus validation

		//Envoie des files descriptors avec excelp (précision des pipes de communication avec validation)
		snprintf(rvalidation, sizeof(rvalidation), "%d", fd3[0]);
		snprintf(wvalidation, sizeof(wvalidation), "%d", fd4[1]);

		execlp("./validation","./validation",rvalidation,wvalidation,NULL);
		printf("erreur\n");
		perror("exec");
		exit(EXIT_FAILURE);
	}
	// le reste du programme acquisition

	//attendre de recevoir une requete du terminal
		//litLigne sur le pipe de lecture du point de vue de Acquisition
	char *requete = litLigne(fd2[0]);
	printf("[acquisition] : Requête de terminal bien reçue. %s",requete);


	//Transmets la requete à validation
	ecritLigne(fd3[1],requete);
	printf("[acquisition] : Requête transmise à validation.\n\n");

	//attendre la réponse de validation
	char *reponse = litLigne(fd4[0]);
	

	printf("[acquisition] : Réponse de validation bien reçue.\n");

	//retransmets la réponse à terminal
	ecritLigne(fd1[1],reponse);
	printf("[acquisition] : Réponse transmise à terminal.\n\n");
	
	wait(NULL);
	return 0;
}