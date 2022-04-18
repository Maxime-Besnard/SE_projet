#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#include "lectureEcriture.h"
#include "message.h"

//test

int main(int argc, char *argv[]){
			
	//recupérer les pipes de lecture et d'écriture
	int lecture=atoi(argv[1]);
	int ecriture=atoi(argv[2]);
	

	//Générer un messsage en utlisant les fonctions de message.h
		//le message contient 3 parties, numTest, requete ou demande, valeur (valeur aléatoire)
		//on est dans terminal on génère le message en étant une Demande

	char num[255], type[255], valeur[255]; 
  	char *requete = message("0001000000000000", "Demande", "15");
	printf("\n[terminal] : La requête a été générée. %s",requete);


	//Vérifie son format en utilisant la fonction decoupe dans message.h
	//Envoie une requete à acquisition
		//Envoie en utilisant la fonction ecritLigne sur le pipe d'écriture

	if(decoupe(requete, num, type, valeur) == 0){
		printf("[terminal] : Erreur de découpage!!\n");
		exit(0);
	}
	printf("[terminal] : Le format de la requête est valide.\n");

	ecritLigne(ecriture, requete);
	printf("[terminal] : La requête a bien été envoyée vers acquisition.\n\n");

	//Attendre la réponse d'acquisition
		//liLigne sur le pipe de lecture
	char *reponse = litLigne(lecture);
	printf("[terminal] : Réponse d'acquisition bien reçue. %s\n", reponse);

	return 0;
}