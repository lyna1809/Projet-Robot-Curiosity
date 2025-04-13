#include<stdio.h>
#include "environnement.h"
#include "programme.h"
#include "observateur.h"
#include "interprete.h"

int main (int argc, char **argv){
   Environnement envt;
   Programme prog ;
   erreur_terrain errt;
   erreur_programme errp;
   etat_inter etat;

   resultat_inter res;
   if(argc>3){
    printf(" <terrain> <programme> \n");
    return 1;
   }
    errt=initialise_environnement(&envt,argv[1]);
    errp = lire_programme(&prog, argv[2]);


    init_etat(&etat);
    do {
        res = exec_pas(&prog, &envt, &etat);
        /* Affichage du terrain et du robot */
        afficher_envt(&envt);
    } while (res == OK_ROBOT );

    if((est_fini((&envt)->e ))==1){
        printf("programme valide pour automate 1 \n");
    }
    else if ((est_fini((&envt)->e ))==0) {
        printf("programme invalide pour automate 1 \n");
    } 
    if (est_fini_def((&envt)->e2)==1){
        printf("programme valide pour automate 2 \n");
    }
    else if (est_fini_def((&envt)->e2 )==0) {
        printf("programme invalide pour automate 2 \n");
    } 
    
return 0;
} 