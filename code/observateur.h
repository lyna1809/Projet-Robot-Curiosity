#ifndef _OBSERVATEUR_H_
#define _OBSERVATEUR_H_

typedef enum {A, D, G, M} Alphabet ;

typedef enum {Init, Mes, Err,Avan,Tour} Etats ;

Etats initital();
Etats transition(Etats e,Alphabet c );
int est_fini(Etats e);

Etats initital_def();
Etats transition_def(Etats e,Alphabet c );
int est_fini_def(Etats e);


#endif 
