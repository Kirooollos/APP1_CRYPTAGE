#include "client.h"
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

#define MAXMSG MAXREP
void decryptage(char *message, char *out) {
        for(int i=0; message[i]!='\0';i++)
        {
            if (('a'<=message[i]) && (message[i]<='z') )
            {
                out[i]=(message[i] -'a' - 5 +26)%26 + 'a';
            }
            else if(('A'<=message[i]) && (message[i]<='Z')){
                out[i]=(message[i] -'A' - 5+26)%26 + 'A';
            }
            else{
                out[i]=message[i];
            }

        }
        
}
int main() {
    char reponse[MAXREP]; // pour stocker la réponse du serveur
    char message[MAXMSG]; // pour stocker le message à envoyer au serveur
    char secret[MAXMSG]; 
    decryptage(message, secret);
    printf ("Réponse du serveur: %s", reponse);
    
    
    
    // Affiche les échanges avec le serveur (false pour désactiver)
    mode_debug(true);

    // Connexion au serveur AppoLab
    connexion("im2ag-appolab.u-ga.fr", 9999);
    // utilisez le port 443 en cas de problème sur le 9999
    /* connexion("im2ag-appolab.u-ga.fr", 443); */

    // Remplacez <identifiant> et <mot de passe> ci dessous.
    envoyer_recevoir("login 12108029 \"HUSSEIN\"", reponse);
    envoyer_recevoir("load projetX", reponse);
    envoyer_recevoir("help", reponse);

    decryptage(reponse, secret);
    envoyer_recevoir(secret, reponse);
    // Notez qu'ici on n'utilise pas la reponse du serveur

    lire_clavier(message);   // message tapé au clavier
    envoyer_recevoir(message, reponse); // on envoie message, et on reçoit la réponse du serveur

    printf ("Réponse du serveur: %s", reponse);

    printf ("Fin de la connection au serveur\n");
    return 0;
}
