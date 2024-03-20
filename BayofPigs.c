#include "client.h"
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

#define MAXMSG MAXREP
#define MAX_SIZE 9999

void supprimer(char *tab, int *taille , int nbcs){
    for(int i=1;i<nbcs;i++){
      // FIX: useless
      //  tab[*taille-2]=tab[*taille-1];
        tab[*taille-1]='\0';
        *taille-=1;
    }
    tab[*taille-1]='\0';
    // FIX: don't forget to reduce size
    *taille -= 1;
}

int tailletab (char *tab){
    int i;
    for(i=0; tab[i]!='\0';i++)
    {
        
    }
    return i;
}

void ajoutdebut(char* enc, char elem, int *taille){
    for(int i=*taille-1 ;i>=0;i--){
        enc[i+1]=enc[i];
    }
    // FIX: end with '\0' !
    enc[*taille+1] = '\0';
    enc[0]=elem;
    *taille+=1;
}



// FIX: on your interface, specify with const the buffer which is read-only (cryptee)
void decrypte(char *decryptee, const char *cryptee){
    int nbcs; //nombre de caracteres à supprimer

    char TXT[MAX_SIZE]="";
    char ENC[MAX_SIZE]="";
    int i;
    for (i = 0; cryptee[i]!='\0'; i++)
    {
        ENC[i]= cryptee[i];
    }
    // FIX: must end the copy with a '\0'
    ENC[i] = '\0';
    printf("Le message a decrypter est : %s \n", ENC);
    int tailleENC=tailletab(ENC);
    int tailleTXT=tailletab(TXT);
    int *ptailleTXT=&tailleTXT;
    int *ptailleENC = &tailleENC;
    while(tailleENC!=0){
        nbcs=ENC[tailleENC-1]%8;
	// FIX: must do it only when nbcs less than size
        //fprintf(stderr, "XXX C: %c %d %d\n", ENC[tailleENC-1], nbcs, tailleTXT);
        if(nbcs>=tailleTXT){
            ajoutdebut(TXT,ENC[tailleENC-1],ptailleTXT);
            supprimer(ENC,ptailleENC,1);
        }
        else{
	  // FIX, must transfer nbcs chars in order from TXT to TXT!
            for(int i=0;i< nbcs;i++){
                ajoutdebut(TXT,TXT[tailleTXT-1],ptailleTXT);
		supprimer(TXT,ptailleTXT,1);
            }

            ajoutdebut(TXT,ENC[tailleENC-1],ptailleTXT);
            supprimer(ENC,ptailleENC,1);
        }
        //fprintf(stderr, "XXX DEC: %s\n", TXT);
        //fprintf(stderr, "XXX ENC: %s\n", ENC);

    }
    
    for(i = 0; TXT[i] != '\0';i++)
	{
		decryptee[i] = TXT[i];
	}
    // FIX: don't forget the terminiating '\0'
    decryptee[i] = '\0';
}


int main() {
    char reponse[MAXREP]; // pour stocker la réponse du serveur
    char message[MAXMSG]; // pour stocker le message à envoyer au serveur

    // FIX: do not print reponse here: it is not initialized!
    //printf ("Réponse du serveur: %s", reponse);
    
    
    
    // Affiche les échanges avec le serveur (false pour désactiver)
    mode_debug(true);

    // Connexion au serveur AppoLab
    connexion("im2ag-appolab.u-ga.fr", 9999);
    // utilisez le port 443 en cas de problème sur le 9999
    /* connexion("im2ag-appolab.u-ga.fr", 443); */

    // Remplacez <identifiant> et <mot de passe> ci dessous.
    envoyer_recevoir("login 12108029 \"HUSSEIN\"", reponse);
    envoyer_recevoir("load BayOfPigs", reponse);
    envoyer_recevoir("help", reponse);

    // FIX: do not decrypt help message, it is a Cesar coding, not a crypteMov!
    //decrypte(reponse,messagedecryptee);

    envoyer_recevoir("start", reponse);
    envoyer_recevoir("Par otuam eriet", reponse);

    char messagedecryptee[MAX_SIZE];

    // FIX: decrypt the message there instead, use the right argument order!
    decrypte(messagedecryptee, reponse);
    envoyer_recevoir(messagedecryptee, reponse);



    lire_clavier(message);   // message tapé au clavier
    envoyer_recevoir(message, reponse); // on envoie message, et on reçoit la réponse du serveur

    printf ("Réponse du serveur: %s", reponse);

    printf ("Fin de la connection au serveur\n");
    return 0;
}