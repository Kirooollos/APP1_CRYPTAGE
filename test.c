#include "client.h"
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

#define MAXMSG MAXREP

void supprimer(char *tab, int *taille , int indice){
    for(int i=indice;i<=*taille;i++){
        tab[i]=tab[i+1];
    }
    *taille-=1;
}  

int tailletab (char *tab){
    int i;
    for(i=0; tab[i]!='\0';i++)
    {
        
    }
    return i;
}

void ajout(char* enc, char elem, int *taille){
    enc[*taille]=elem;
    enc[*taille+1] = '\0';
    *taille+=1;
}

int trouverIndiceCaractere(const char *chaine, char caractere) {
    int indice = -1;  // Initialise l'indice à -1 pour indiquer qu'aucune correspondance n'a été trouvée
    int i = 0;

    while (chaine[i] != '\0') {
        if (chaine[i] == caractere) {
            indice = i;  // Enregistre l'indice où le caractère a été trouvé
            break;  // Sort de la boucle dès que la première occurrence est trouvée
        }
        i++;
    }

    return indice;
}
// FIX: on your interface, specify with const the buffer which is read-only (cryptee)
void crypteSeq(const char *decryptee, char *cryptee){
    char Seq[9999]="";
    char Output[9999]="";
    char Input[9999]="";
    char tmp;
    int i;
    for (i = 0; decryptee[i]!='\0'; i++)
    {
        Input[i]= decryptee[i];
    }
    // FIX: must end the copy with a '\0'
    Input[i] = '\0';
    printf("Le message a crypter est : %s \n", Input);
    int tailleInput=tailletab(Input);
    int tailleSeq= tailletab(Seq);
    int tailleOutput= tailletab(Output);
    int *ptailleOutput=&tailleOutput;
    int *ptailleSeq= &tailleSeq;
    
    for(int j=0;j<=tailleInput;j++){
        int indice= trouverIndiceCaractere(Seq,Input[j]);
        if(indice==-1){
            ajout(Seq,Input[j],ptailleSeq);
            ajout(Output,Input[j],ptailleOutput);
        }
        else{
            if(indice==0){
                ajout(Output,Seq[tailleSeq-1],ptailleOutput);
                tmp=Seq[0];
                supprimer(Seq, ptailleSeq,0);
                ajout(Seq,tmp,ptailleSeq);
            }
            else{
                ajout(Output,Seq[indice-1],ptailleOutput);
                tmp=Seq[indice];
                supprimer(Seq,ptailleSeq,indice);
                ajout(Seq,tmp,ptailleSeq);
                
            }
        }
    }
    for(i = 0; Output[i] != '\0';i++)
	{
		cryptee[i] = Output[i];
	}
    // FIX: don't forget the terminiating '\0'
    cryptee[i] = '\0';
}

int main(){
char TXT[999]="Alice, nous avons besoin de toi de toute urgence.";
char ENC[999]="";
/*int tailleTXT=strlen(TXT);
int *ptailleTXT=&tailleTXT;
int tailleENC=strlen(ENC);
int *ptailleENC=&tailleENC;*/
//supprimer(TXT,ptaille,3);
crypteSeq(TXT,ENC);
printf("%s\n",TXT);
printf("%s\n",ENC);

}
