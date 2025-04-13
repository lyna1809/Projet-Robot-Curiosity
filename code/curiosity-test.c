#include<stdio.h>
#include "interprete.h"
#include "programme.h"
#include "environnement.h"
#include "terrain.h"
#include "observateur.h"
#include <stdlib.h>
#include <string.h>

void gestion_erreur_terrain(erreur_terrain e) {
  switch (e) {
  case OK:
    break;
  case ERREUR_FICHIER:
    printf("Erreur lecture du terrain : erreur d'ouverture du fichier\n");
    exit(1);
  case ERREUR_LECTURE_LARGEUR:
    printf("Erreur lecture du terrain : erreur de lecture de la largeur\n");
    exit(1);
  case ERREUR_LECTURE_HAUTEUR:
    printf("Erreur lecture du terrain : erreur de lecture de la hauteur\n");
    exit(1);
  case ERREUR_LARGEUR_INCORRECTE:
    printf("Erreur lecture du terrain : largeur incorrecte\n");
    exit(1);
  case ERREUR_HAUTEUR_INCORRECTE:
    printf("Erreur lecture du terrain : hauteur incorrecte\n");
    exit(1);
  case ERREUR_CARACTERE_INCORRECT:
    printf("Erreur lecture du terrain : caractère incorrect\n");
    exit(1);
  case ERREUR_LIGNE_TROP_LONGUE:
    printf("Erreur lecture du terrain : ligne trop longue\n");
    exit(1);
  case ERREUR_LIGNE_TROP_COURTE:
    printf("Erreur lecture du terrain : ligne trop courte\n");
    exit(1);
  case ERREUR_LIGNES_MANQUANTES:
    printf("Erreur lecture du terrain : lignes manquantes\n");
    exit(1);
  case ERREUR_POSITION_ROBOT_MANQUANTE:
    printf(
        "Erreur lecture du terrain : position initiale du robot manquante\n");
    exit(1);
  }
}

void affichage_position_programme(erreur_programme e) {
  int i;
  printf("Ligne %d, colonne %d :\n", e.num_ligne, e.num_colonne);
  printf("%s\n", e.ligne);
  /* Impression de e.num_colonne-1 espaces */
  for (i = 1; i < e.num_colonne; i++) {
    printf(" ");
  }
  /* Impression d'un curseur de position */
  printf("^\n");
}

void gestion_erreur_programme(erreur_programme e) {
  switch (e.type_err) {
  case OK_PROGRAMME:
    break;
  case ERREUR_FICHIER_PROGRAMME:
    printf("Erreur lecture du programme : erreur d'ouverture du fichier\n");
    exit(2);
  case ERREUR_BLOC_NON_FERME:
    printf("Erreur lecture du programme : bloc non fermé\n");
    exit(2);
  case ERREUR_FERMETURE_BLOC_EXCEDENTAIRE:
    printf("Erreur lecture du programme : fermeture de bloc excédentaire\n");
    affichage_position_programme(e);
    exit(2);
  case ERREUR_COMMANDE_INCORRECTE:
    printf("Erreur lecture du programme : commande incorrecte\n");
    affichage_position_programme(e);
    exit(2);
  }
}



int main(int argc, char **argv) {
  Environnement envt;
  Programme prog;
  erreur_terrain errt;
  erreur_programme errp;
  etat_inter etat;
  resultat_inter res;
  char nom_terrain[1000];
  char nom_programme[1000];
  char Orien;
  char resultat_attendu;
  int Nmax,X,Y,x,y;
  FILE *f;
  
  if (argc < 2) {
    printf("Usage: %s <terrain> <programme>\n", argv[0]);
    return 1;
  }

  f=fopen(argv[1],"r");
  fgets(nom_terrain, sizeof(nom_terrain), f);
  fgets(nom_programme, sizeof(nom_programme), f);
  nom_terrain[strlen(nom_terrain)-1]='\0';
  nom_programme[strlen(nom_programme)-1]='\0';

  fscanf(f," %d \n",&Nmax);

  fscanf(f," %c",&resultat_attendu);
  
  fscanf(f," %d",&X);
  
  fscanf(f," %d",&Y); //l'espace
  
  fscanf(f," %d",&Y);
  
  fscanf(f,"%c",&Orien);
  
  fclose(f);
  

  errt = initialise_environnement(&envt, nom_terrain);
  gestion_erreur_terrain(errt);

  errp = lire_programme(&prog, nom_programme);
  gestion_erreur_programme(errp);

  /* Initialisation de l'état */
  init_etat(&etat);
  do {
    res = exec_pas(&prog, &envt, &etat);
    Nmax--;
    /* Affichage du terrain et du robot */
    afficher_envt(&envt);
  } while (res == OK_ROBOT && Nmax !=0);

  /* Affichage du résultat */
  switch (res) {
  case OK_ROBOT:
    if(resultat_attendu=='N' ){
          position(&envt.r, &x, &y);
          if(X==x+1 && Y==y+1 ){
            if(Orien=='E' && orient(&envt.r)==Est){
              printf("OK \n");
              printf("une position normale à l'intérieur du terrain \n");}
            else if(Orien=='N' && orient(&envt.r)==Nord){
              printf("OK \n");
              printf("une position normale à l'intérieur du terrain \n");}
            else if(Orien=='O' && orient(&envt.r)==Ouest){
              printf("OK \n");
              printf("une position normale à l'intérieur du terrain \n");}
            else if(Orien=='S' && orient(&envt.r)==Sud){
              printf("OK \n");
              printf("une position normale à l'intérieur du terrain \n");}
            
          }
          else {
              printf("Positions ou orientation non coherentes avec celle attendu pour N  \n");
          }
      }
    else {
      printf("resultat non attendu N\n");
    }
    break;
  case SORTIE_ROBOT:
    if(resultat_attendu=='S'){
          printf("OK \n");
          printf("robot est sorti du terrain \n");
      }
    else{
          printf("Non compatible avec le resultat attendu:Sortie_innatendu \n");
    }
    break;
  case ARRET_ROBOT:
    if(resultat_attendu=='F'){
          position(&envt.r, &x, &y);
          if(X==x+1 && Y==y+1 ){
            if(Orien=='E' && orient(&envt.r)==Est){
              printf("OK \n");
              printf("programme est terminé \n");}
            else if(Orien=='N' && orient(&envt.r)==Nord){
              printf("OK \n");
              printf("programme est terminé \n");}
            else if(Orien=='O' && orient(&envt.r)==Ouest){
              printf("OK \n");
              printf("programme est terminé \n");}
            else if(Orien=='S' && orient(&envt.r)==Sud){
              printf("OK \n");
              printf("programme est terminé \n");}  
          }
          else {
              printf("Positions ou orientation non coherentes avec celle attendu . \n");
          }
      }
    else {

      printf("resultat non attendu F \n");
    }

    break;
  case PLOUF_ROBOT:
    if(resultat_attendu=='P'){
        printf("OK \n");
        printf(" robot est tombé dans l'eau \n");
    }
    else{
      printf("Non compatible avec le resultat attendu:tomber dans l'eau innatendu \n");
    }
    break;

  case CRASH_ROBOT:
    if(resultat_attendu=='O'){
          printf("OK \n");
          printf("robot a rencontré un obstacle\n");
      }
    else{
          printf("Non compatible avec le resultat attendu:crash_innatendu \n");
    }
    break;
  case ERREUR_PILE_VIDE:
    printf("ERREUR : pile vide\n");
    break;
  case ERREUR_ADRESSAGE:
    printf("ERREUR : erreur d'adressage\n");
    break;
  case ERREUR_DIVISION_PAR_ZERO:
    printf("ERREUR : division par 0\n");
    break;
  }
}

  