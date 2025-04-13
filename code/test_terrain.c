#include "terrain.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
  FILE *f,*fich;
  Terrain t;
  int x, y;

  
  if (argc < 2) {
    printf("Usage : %s <fichier>\n", argv[0]);
    return 1;
  }
  f = fopen(argv[1], "r");

  if( lire_terrain(f, &t, &x, &y)==ERREUR_FICHIER) {
    printf("Donne moi un autre fichier \n");
    char nomFichier[100]; 
    scanf("%s", nomFichier);
    fich = fopen(nomFichier, "r");
     
    if (lire_terrain(fich, &t, &x, &y)==ERREUR_FICHIER){
      return 1 ;
    }
    else{
      lire_terrain(fich, &t, &x, &y);
      fclose(fich); }
  }
  else{
    lire_terrain(f, &t, &x, &y);
    fclose(f);
  }
  afficher_terrain(&t);
  printf("Position initiale du robot : (%d, %d)\n", x, y); 
}

