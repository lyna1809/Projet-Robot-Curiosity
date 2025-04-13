#include "environnement.h"
#include "interprete.h"
#include "programme.h"
#include "generation_terrains.h"
#include "terrain.h"
#include "observateur.h" 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main(int argc, char **argv){
    erreur_terrain errt;
    erreur_programme errp;
    Environnement envt;
    etat_inter etat; 
    resultat_inter res;
    Programme prog;
    FILE *fichier_res;
    Terrain T;
    FILE *terrain_tmp;
    int N , l,graine, h,nb_step_max,cmp,pas=0;
    float d;
    int nbr_sortie=0, nbr_obstacle=0 , nbr_bloque=0;

    if (argc < 9) {
        printf(
        "Usage: %s <fichier_programme> <N> <L> <H> <d> <graine> <nb_step_max> <fichier_res> \n",
        argv[0]);
        return 1;
    }

    N = strtol(argv[2], NULL, 10);
    l = strtol(argv[3], NULL, 10);
    h = strtol(argv[4], NULL, 10);
    d = strtof(argv[5], NULL);
    graine=strtol(argv[6], NULL, 10);
    srand(graine);

    fichier_res=fopen(argv[8],"w");
    fprintf(fichier_res, "%d\n", N);
    printf("%d\n", l/2);
    printf("%d\n", h/2);

    int i=0;
    while(i<N){
       
        generation_aleatoire(&T,l,h,d);
        while(existe_chemin_vers_sortie(&T)!=1){
           generation_aleatoire(&T,l,h,d);
        }
        
        terrain_tmp=fopen("terrain_exo3","w");
        int k, m;
        char c;
        fprintf(terrain_tmp, "%d\n", l);
        fprintf(terrain_tmp, "%d\n", h);
        for (m = 0; m < h; m++) {
            for (k = 0; k < l; k++) {
                switch (T.tab[k][m]) {
                case LIBRE:
                   c = '.';
                   break;
                case ROCHER:
                   c = '#';
                   break;
                case EAU:
                   c = '~';
                   break;
                }
                if (k ==l/2  && m == h/2){
                   c = 'C';
                } 
                fprintf(terrain_tmp, "%c", c);
            }
            fprintf(terrain_tmp, "\n");
            }
        fprintf(terrain_tmp, "\n");
        fclose(terrain_tmp);

        
        errt=initialise_environnement(&envt,"terrain_exo3");
        errp = lire_programme(&prog, argv[1]);

        cmp=0;
        nb_step_max=strtol(argv[7], NULL, 10);

        init_etat(&etat);
        do {
            int x=envt.r.x;
            int y=envt.r.y;
            res = exec_pas(&prog, &envt, &etat);
            nb_step_max--;
            if(envt.r.x!=x || envt.r.y!=y ){
                cmp++;}
            /* Affichage du terrain et du robot */
            afficher_envt(&envt);
        } while (res == OK_ROBOT && nb_step_max !=0);
        
        switch (res) {
        case OK_ROBOT:
            printf("Robot sur une case libre, programme non terminé (ne devrait pas "
                "arriver)\n");
            break;
        case SORTIE_ROBOT:
            fprintf(fichier_res, "%d\n", cmp); 
            pas+=cmp;
            nbr_sortie++;
            break;
        case ARRET_ROBOT:
            fprintf(fichier_res, "%d\n", -1); 
            nbr_bloque++;
            break;
        case PLOUF_ROBOT:
            fprintf(fichier_res, "%d\n", -2); 
            nbr_obstacle++;
            break;
        case CRASH_ROBOT:
            fprintf(fichier_res, "%d\n", -3); 
            nbr_obstacle++;
            break;
        case ERREUR_PILE_VIDE:
            printf("ERREUR : pile vide\n");
            break;
        case ERREUR_ADRESSAGE:
            printf("ERREUR : erreur d'adressage\n");
            break;
        case ERREUR_DIVISION_PAR_ZERO:
            printf("ERREUR : division par 0\n");
            break; }
    printf("passer à un autre terrain\n");
    i++;}
printf("Moyenne sortie:%f\n",(float)nbr_sortie/(float)N);
printf("Moyenne bloque:%f\n", (float)nbr_bloque/(float)N);
printf("Moyenne obstacle:%f\n", (float)nbr_obstacle/(float)N);
printf("Moyenne pas effectué pour sortie:%f\n", (float)pas/(float)nbr_sortie);

return 0;
}
