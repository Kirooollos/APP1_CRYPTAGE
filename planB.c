#include "client.h"
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#define MAXMSG MAXREP


int longueur(char tableau[]){
    int i = 0;
    while(tableau[i]!='\0'){
        // printf("le %d ieme caractere correspond a %c\n", i,tableau[i]);
        i++;
    }
    return i;
}

char codage_x (int x, char lettreLue){
    char lettreSuivantex;
    if ((('a' <= lettreLue) && (lettreLue <= 'z'))){
        lettreSuivantex = ((lettreLue-97+x+26)%26)+97;
    } else if ((('A' <= lettreLue) && (lettreLue <= 'Z')))
    {
        lettreSuivantex = ((lettreLue-65+26+x)%26)+65;
    }else {
        lettreSuivantex = lettreLue;
    }

    // printf("\n%c\n",lettreSuivantex);
    return lettreSuivantex;
}

void traitement( int x,char in[], char out[]){
    for(int i = 0;i<longueur(in);i++){
        out[i]=codage_x(x,in[i]);
    }
}



int main() {
    int x;
    char phrase[1000];
    char * output = malloc(1000);
    output[0]='\0';
    strcpy(phrase,"hasta la revolucion");

    char reponse[MAXREP]; // pour stocker la réponse du serveur
    // char message[MAXMSG]; // pour stocker le message à envoyer au serveur

    // Affiche les échanges avec le serveur (false pour désactiver)
    mode_debug(true);

    // Connexion au serveur AppoLab
    connexion("im2ag-appolab.u-ga.fr", 9999);
    // utilisez le port 443 en cas de problème sur le 9999
    /* connexion("im2ag-appolab.u-ga.fr", 443); */

    // Remplacez <identifiant> et <mot de passe> ci dessous.
    envoyer_recevoir("login 12108029 HUSSEIN", reponse);
    envoyer_recevoir("load planB", reponse);
    envoyer_recevoir("aide", reponse);
    x = reponse[0]-67;
    printf("%c - %c = %d\n",reponse[0],'C',x );
    traitement(-x,phrase,output);
    envoyer_recevoir("start", reponse);
    // envoyer_recevoir("42", reponse);
    envoyer_recevoir(output, reponse);      
    // Notez qu'ici on n'utilise pas la reponse du serveur
    printf ("Réponse du serveur: %s", reponse);    
    // lire_clavier(message);   // message tapé au clavier
    

    printf ("Fin de la connection au serveur\n");
    return 0;
}