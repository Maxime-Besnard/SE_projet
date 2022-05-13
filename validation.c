#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#include "lectureEcriture.h"
#include "message.h"
#include "alea.h"

int main(int argc, char *argv[]){

	//recupérer les pipes de lecture et d'écriture
	int lecture=atoi(argv[1]);
	int ecriture=atoi(argv[2]);
	
	//attend la requete depuis acquisition

	char *requete = litLigne(lecture);
	printf("[validation] : Requête d'acquisition bien reçue.\n");



	//verifie le contenu du message 
		//il a recu un msg, ce msg il va le découper en 3 morceau en utilisant decoupe de message.h
		//il vérifie que le 1er morceau qui est le numéro du test pcr est identique à celui généré par terminal
	
	char num[255], type[255], valeur[255]; 
  	decoupe(requete, num, type, valeur);
	
	char* valide = "1";

	if(strcmp(num, "0001000000000000") != 0 && strcmp(num, "0001000111000001") != 0){
		printf("[validation] : Erreur de correspondance !!\n");
		valide = "0";
	}
	else if(atoi(valeur) > 10){
		printf("[validation] : Date de validité dépassée !!\n");
		valide = "0";
	}
	else{
		printf("[validation] : Le numéro de test PCR correspond.\n");
	}
	


	//retransmets une reponse à acquisition
		//génere un msg de type Reponse et de valeur 1 si test valide 0 sinon

	char *reponse = message(num, "Reponse", valide);
	printf("[validation] : La réponse a bien été générée. %s", reponse);

	ecritLigne(ecriture, reponse);
	printf("[validation] : La réponse a bien été envoyée vers acquisition.\n\n");
	
	return 0;

}