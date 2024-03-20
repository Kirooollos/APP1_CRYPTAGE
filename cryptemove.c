#include "client.h"
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

#define MAXMSG MAXREP
#define MAX_SIZE 9999

int tailletab (char *tab){
    int i;
    for(i=0; tab[i]!='\0';i++)
    {
        
    }
    return i;
}
void supprimer(char *tab, int *taille){
    for ( int i = 0; i <*taille ; i++)
    {
        tab[i]= tab[i+1];   
    }
    tab[*taille] = '\0';
    

    
}

void ajout(char *tab, char *tab2){
    
    strncat(tab2,tab,1);    

}

void crypte(char *acryptee, char *cryptee){
    int x;
    char tmp[MAX_SIZE]="";
    char TXT[MAX_SIZE]="";
    char ENC[MAX_SIZE]="";
    for (int i = 0; acryptee[i]!='\0'; i++)
    {
        TXT[i]= acryptee[i];
    }
    printf("Le message a crypter est : %s \n", TXT);
    int tailleTXT=tailletab(TXT);
    int *ptailleTXT = &tailleTXT;
    while(tailleTXT!=0){
        x=TXT[0]%8;
        ajout(TXT,ENC);
        supprimer(TXT,ptailleTXT);
        for(int j=0; j<x;j++){
            ajout(TXT,tmp);
            supprimer(TXT,ptailleTXT);
        }
        tailleTXT=tailleTXT-1;
        strcat(TXT,tmp);
        strcpy(tmp,"");
    
        
    }
    for(int i = 0; ENC[i] != '\0';i++)
	{
		cryptee[i] = ENC[i];
	}
}


int main() {
    char reponse[MAXREP]; // pour stocker la réponse du serveur
    char message[MAXMSG]; // pour stocker le message à envoyer au serveur
    printf ("Réponse du serveur: %s", reponse);
    
    
    
    // Affiche les échanges avec le serveur (false pour désactiver)
    mode_debug(true);

    // Connexion au serveur AppoLab
    connexion("im2ag-appolab.u-ga.fr", 9999);
    // utilisez le port 443 en cas de problème sur le 9999
    /* connexion("im2ag-appolab.u-ga.fr", 443); */

    // Remplacez <identifiant> et <mot de passe> ci dessous.
    envoyer_recevoir("login 12108029 \"HUSSEIN\"", reponse);
    envoyer_recevoir("load crypteMove", reponse);
    envoyer_recevoir("help", reponse);
    char messagecrypter[MAX_SIZE];
	crypte(reponse, messagecrypter); 

    envoyer_recevoir("start", reponse);
	envoyer_recevoir(messagecrypter, reponse);
    // Notez qu'ici on n'utilise pas la reponse du serveur

    lire_clavier(message);   // message tapé au clavier
    envoyer_recevoir(message, reponse); // on envoie message, et on reçoit la réponse du serveur

    printf ("Réponse du serveur: %s", reponse);

    printf ("Fin de la connection au serveur\n");
    return 0;
}