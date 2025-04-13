#include <stdio.h>
#include "observateur.h"

//Automate 1
Etats initital(){
    return Init;
}


int est_fini(Etats e){ 
    if(e==Init || e==Mes){
        return 1;
    }
    else{
        return 0;
    }
}

Etats transition(Etats e,Alphabet c ){
    switch(e){
        case Init :
            switch(c){
               case A :
                  return Err;
               case D:
                  return Init; 
               case G:
                  return Init;
               case M :
                  return Mes;   
            }
            break;


        case Mes :
            switch(c){
                case A :
                    return Init;
                case D:
                    return Init;
                case G:
                    return Init;
                case M :
                    return Mes; 
                
            }
            break;

        case Err :
            switch(c){
                case A :
                   return Err;
                case D:
                   return Err;
                case G:
                   return Err;
                case M :
                   return Err;
                
            }
            break;
        default:
            printf("cet etat n'existe pas \n");
            return Err;
        
    }
}


//Automate2

Etats initital_def(){
    return Init;
}


int est_fini_def(Etats e){
    if(e==Init || e==Mes || e==Avan ){
        return 1;
    }
    else{
        return 0;
    }
}

Etats transition_def(Etats e,Alphabet c ){
    switch(e){
        case Init :
            switch(c){
                case M :
                  return Mes;
                case A:
                  return Err;
                case D:
                  return Tour;
                case G :
                  return Tour;
                default :
                  printf("erreur\n");
            }
            break;


        case Tour :
            switch(c){
                case  M: 
                    return Mes;
                case A:
                    return Err;
                case D:
                    return Err;
                case G :
                    return Err;
                default :
                  printf("erreur \n"); 
            }
            break;

        case Mes :
            switch(c){
                case M :
                   return Mes;
                case A:
                   return Avan;
                case D:
                   return Tour;
                case G :
                   return Tour;
                default :
                  printf("erreur\n");
            }
            break;

        case Avan :
            switch(c){
                case M :
                   return Mes;
                case A:
                   return Err;
                case D:
                   return Tour;
                case G :
                   return Tour;
                default :
                  printf("erreur \n");
            }
            break;
        case Err :
            switch(c){
                case M :
                   return Err;
                case A:
                   return Err;
                case D:
                   return Err;
                case G :
                   return Err;
                default :
                  printf("erreur \n");
            }
            break;
        default :
            printf("erreur \n");
    }
}