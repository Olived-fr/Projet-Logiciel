#ifndef persistance_h
#define persistance_h

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "../Structure/plateau.h"

bool verif_file(char *name);
void creation_config();
void board_save(Plateau p);
void historique(bool b, Coordonnees_tab cor, Couleur co);
void dernier_coup(char couleur[], int *abscisse, int *ordonnee);
void chargement(Plateau p);
void annuler(Plateau p);


#endif