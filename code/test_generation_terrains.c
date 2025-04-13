#include "generation_terrains.h"
#include "terrain.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int nb_cases_occupees(Terrain *T) {
  int occupee = 0;
  int x, y;
  for (x = 0; x < largeur(T); x++) {
    for (y = 0; y < hauteur(T); y++) {
      if (T->tab[x][y] != LIBRE)
        occupee++;
    }
  }
  return occupee; 
}

// Test de generation aléatoire de terrains
// Le programme génère n terrains de largeur et hauteur fixes
// avec largeur et hauteur impaires et inférieures a dimension_max de terrain.h
// avec densité d'obstacle dObst
// autre que la case centrale soit occupee
// l'appel du programme se fait avec 5 arguments :
// generation_terrains N largeur hauteur dObstacle fichier_res
// la sortie se fait dans le fichier resultat

int main(int argc, char **argv) {
  int N, i, l, h,cmpN;
  float dObst;
  FILE *resFile;
  Terrain T; 
  float D_moyenne=0;
 
  if (argc < 6) {
    printf(
        "Usage: %s <N> <largeur> <hauteur> <densite_obstacle> <fichier_res> \n",
        argv[0]);
    return 1;
  }

  N = strtol(argv[1], NULL, 10); 
  l = strtol(argv[2], NULL, 10);
  h = strtol(argv[3], NULL, 10);
  dObst = strtof(argv[4], NULL);

  // test de l et h
  if (l > DIM_MAX || l % 2 == 0) {
    printf("Largeur incorrecte : doit être impaire et <= %d\n", DIM_MAX);
    return 1;
  }
  if (h > DIM_MAX || h % 2 == 0) {
    printf("Hauteur incorrecte : doit être impaire et <= %d\n", DIM_MAX);
    return 1;
  }
  if ((dObst > 1) || (dObst < 0)) {
    printf("Densité incorrecte : doit être comprise entre 0 et 1\n");
    return 1;
  }

  // Ouverture du fichier résultat
  resFile = fopen(argv[5], "w");
  // Écriture du nombre de terrains
  fprintf(resFile, "%d\n", N);
  int genere=0;
  float moyenne_valide;
  cmpN=0;
  int genere_valide=0;
  srand(time(NULL));
  while(cmpN<N){
    int genere_invalide_cmp=0;
    generation_aleatoire(&T,l,h,dObst);
    while(existe_chemin_vers_sortie(&T)!=1){
          generation_aleatoire(&T,l,h,dObst);
          genere_invalide_cmp++;
          genere++;
    }
    genere_valide++;
    if(genere_invalide_cmp==0){
      genere++;
    }
    
    float D = (float)nb_cases_occupees(&T)/(float)(l*h);
    fprintf(resFile, "%f\n", D); 
    i=0;
    while(i<h){
      int j=0;
      while(j<l){
        if (j ==l/2  && i == h/2){
                  fprintf(resFile, "%c", 'C');;
        }
        if(j==l-1){
          switch (T.tab[i][j]) {
                case LIBRE:
                  fprintf(resFile,"%c\n", '.');
                  break;
                case ROCHER:
                  fprintf(resFile, "%c\n", '#');
                  break;
                case EAU:
                  fprintf(resFile, "%c\n", '~');
                  break;
                }  
        }    
        else {
          switch (T.tab[i][j]) {
                case LIBRE:
                  fprintf(resFile,"%c",'.');
                  break;
                case ROCHER:
                  fprintf(resFile, "%c", '#');
                  break;
                case EAU:
                  fprintf(resFile, "%c", '~');
                  break;
                }   
        }
        j++;}
    i++;} 
    D_moyenne=D_moyenne+D;
    cmpN++;}

fprintf(resFile, "%f\n", D_moyenne/N);
moyenne_valide=(float)genere_valide/(float)genere;
fprintf(resFile, "%f\n", moyenne_valide); 
fclose(resFile);
return 0; 
}


