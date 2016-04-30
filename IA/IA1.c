#include "IA.h"

Coordonnees_tab coup_IA1(Plateau p, Couleur couleur_courante)
{	
	int x,y,d1,d2,distance_choisie;
	int distance_min=LIGNE_MAX+1;
	//afin de s'assurer que la première itération génerera une distance min
	int(*distance_extremite1)(Plateau,Type_Case*,bool verif1[LIGNE_MAX][COLONNE_MAX],Couleur);
	int(*distance_extremite2)(Plateau,Type_Case*,bool verif2[LIGNE_MAX][COLONNE_MAX],Couleur);
	int(*distance_choisie)(Plateau,Type_Case*,Type_Case prev,Couleur);
	Type_Case*(voisin_elu)(Type_Case);
	Type_Case case_courante;
	Type_Case case_proche;
	bool verif1[LIGNE_MAX][COLONNE_MAX];
	bool verif2[LIGNE_MAX][COLONNE_MAX];
	initialiser_verif(verif1);
	initialiser_verif(verif2);
	if(couleur_courante==bleu)
	{
		distance_extremite1=&distance_bord_ouest;
		distance_extremite2=&distance_bord_est;
	}
	else
	{
		distance_extremite1=&distance_bord_nord;
		distance_extremite2=&distance_bord_sud;
	}
	//si le plateau est de taille 11 par exemple la distance maximale qu'une case peut avoir à un bord est égal à 10
	bool horizontal=(couleur_courante==bleu)
	if(horizontal)
		distance_min=LIGNE_MAX-1;
	else
		distance_min=COLONNE_MAX-2;
	//Note : cette instruction conditionnelle est facultative car on admet que LIGNE_MAX est toujours égal à COLONNE_MAX
	Coordonnees_tab coordonnees_courantes;
	for(x=0;x<LIGNE_MAX;x++)
	{
		for(y=0;y<COLONNE_MAX;y++)
		{
			case_courante=&p[x][y];
			if(case_courante.coul==couleur_courante)
			{
				d1=distance_extremite1(p,case_courante,verif1,couleur_courante);
				d2=distance_extremite2(p,case_courante,verif2,couleur_courante);
				/*le troisième argument n'a aucun interêt ici, il n'est utile que dans le cas d'un appel récursif pour éviter de tourner en rond*/
				if(d1 < distance_min && d1!=0)
				{
					case_proche=case_courante;
					distance_choisie=distance_extremite1;
				}
				if(d2 < distance_min && d2!=0)
				{
					case_proche=case_courante;
					distance_choisie=distance_extremite2;
				}
				/*Ainsi, on retient la distance la plus courte et on retient également la direction la plus courte avec la variable "distance_choisie"*/
			}
		}
	}
	/* case_proche contient la case la plus proche d'un bord parmi ses voisins neutres on regarde celui qui est
	le plus proche du bord concerné*/
	
	int distance_courante;
	distance_courante=distance_choisie(p,case_proche.NO);
	if(distance_courante < distance_min && case_proche.NO->coul==neutre)
		voisin_elu=&voisin_NO;
	
	distance_courante=distance_choisie(p,case_proche.NE);
	if(distance_courante < distance_min && case_proche.NE->coul==neutre)
		voisin_elu=&voisin_NE;
	
	distance_courante=distance_choisie(p,case_proche.O);
	if(distance_courante < distance_min && case_proche.O->coul==neutre)
		voisin_elu=&voisin_O;
	
	distance_courante=distance_choisie(p,case_proche.SO);
	if(distance_courante < distance_min && case_proche.SO->coul==neutre)
		voisin_elu=&voisin_SO;
	
	distance_courante=distance_choisie(p,case_proche.SE);
	if(distance_courante < distance_min && case_proche.SE->coul==neutre)
		voisin_elu=&voisin_SE;
	
	distance_courante=distance_choisie(p,case_proche.E);
	if(distance_courante < distance_min && case_proche.E->coul==neutre)
		voisin_elu=&voisin_E;
	
	Type_Case* case_choisie=voisin_elu(case_proche);
	/*et on pose le pion à cet endroit là*/
	return case_choisie->co;
}

void initialiser_verif(bool verif[LIGNE_MAX][COLONNE_MAX])
{
	int x,y;
	for(x=0;x<COLONNE_MAX;x++)
		for(y=0;y<LIGNE_MAX;y++)
			verif[x][y]=false;
}

bool impasse(Type_Case c,Couleur cou,bool verif[LIGNE_MAX][COLONNE_MAX],)
{
	bool NE,NO,O,E,SO,SE; //chaque booleen indique true si la case concernée est libre
	/* une case est dite libre si elle n'a pas déjà été vérifiée et si elle n'est pas de la couleur de l'adversaire */
	NE=(c.NE->coul!=changer_joueur(cou) && !verif[c.co.abscisse+1][c.co.ordonnee-1]);
	NO=(c.NO->coul!=changer_joueur(cou) && !verif[c.co.abscisse-1][c.co.ordonnee-1]);
	E=(c.E->coul!=changer_joueur(cou) && !verif[c.co.abscisse+1][c.co.ordonnee]);
	O=(c.O->coul!=changer_joueur(cou) && !verif[c.co.abscisse-1][c.co.ordonnee]);
	SE=(c.SE->coul!=changer_joueur(cou) && !verif[c.co.abscisse+1][c.co.ordonnee+1]);
	SO=(c.SO->coul!=changer_joueur(cou) && !verif[c.co.abscisse-1][c.co.ordonnee+1]);
	return (NE && NO && E && O && SE && SO);
}

int distance_bord_ouest(Plateau p,Type_Case c,bool verif[LIGNE_MAX][COLONNE_MAX],Couleur cou)
{
	initialiser_verif(verif);
	verif[c.co.abscisse][c.co.ordonnee]=true;
	int distance=0;
	if(c.O==NULL)
		return 0;
	else
	{
		if(impasse(c,cou,verif))return LIGNE_MAX+1;
		else
		{
			if(c.O->coul!=changer_joueur(cou) && !verif[c.co.abscisse-1][c.co.ordonnee-1])
				distance=1+distance_bord_ouest(p,&c.O,verif,cou);
			else
			{
				if(c.NO->coul!=changer_joueur(cou) && !verif[c.co.abscisse][c.co.ordonnee+1])
					distance=1+distance_bord_ouest(p,&c.NO,verif,cou);
				else 
				{
					if(c.NE->coul!=changer_joueur(cou) && !verif[c.co.abscisse+1][c.co.ordonnee-1])
						distance=1+distance_bord_ouest(p,&c.NE,verif,cou);
					else
					{
						if(c.E->coul!=changer_joueur(cou) && !verif[c.co.abscisse][c.co.ordonnee-1])
							distance=1+distance_bord_ouest(p,&c.E,verif,cou);
						else
						{
							if(c.SE->coul!=changer_joueur(cou) && !verif[c.co.abscisse+1][c.co.ordonnee+1])
								distance=1+distance_bord_ouest(p,&c.SE,verif,cou);
							else
							{
								if(c.SO->coul!=changer_joueur(cou) && !verif[c.co.abscisse-1][c.co.ordonnee+1])
									distance=1+distance_bord_ouest(p,&c.SO,verif,cou);
							}
						}
					}
				}
			}
		}
	}
	return distance;
}	

int distance_bord_est(Plateau p,Type_Case c,bool verif[LIGNE_MAX][COLONNE_MAX],Couleur cou)
{
	initialiser_verif(verif);
	verif[c.co.abscisse][c.co.ordonnee]=true;
	int distance=0;
	if(c.E==NULL)
		return 0;
	else
	{
		if(impasse(c,cou,verif))return LIGNE_MAX+1;
		else
		{
			if(c.E->coul!=changer_joueur(cou) && !verif[c.co.abscisse-1][c.co.ordonnee-1])
				distance=1+distance_bord_ouest(p,&c.O,verif,cou);
			else
			{
				if(c.NO->coul!=changer_joueur(cou) && !verif[c.co.abscisse-1][c.co.ordonnee-1])
					distance=1+distance_bord_ouest(p,&c.NO,verif,cou);
				else 
				{
					if(c.NE->coul!=changer_joueur(cou) && !verif[c.co.abscisse+1][c.co.ordonnee-1])
						distance=1+distance_bord_ouest(p,&c.NE,verif,cou);
					else
					{
						if(c.E->coul!=changer_joueur(cou) && !verif[c.co.abscisse+1][c.co.ordonnee])
							distance=1+distance_bord_ouest(p,&c.E,verif,cou);
						else
						{
							if(c.SE->coul!=changer_joueur(cou) && !verif[c.co.abscisse+1][c.co.ordonnee+1])
								distance=1+distance_bord_ouest(p,&c.SE,verif,cou);
							else
							{
								if(c.SO->coul!=changer_joueur(cou) && !verif[c.co.abscisse-1][c.co.ordonnee+1])
									distance=1+distance_bord_ouest(p,&c.SO,verif,cou);
							}
						}
					}
				}
			}
		}
	}
	return distance;
}

int distance_bord_nord(Plateau p,Type_Case c,bool verif[LIGNE_MAX][COLONNE_MAX],Couleur cou);
int distance_bord_sud(Plateau p,Type_Case c,bool verif[LIGNE_MAX][COLONNE_MAX],Couleur cou);

Type_Case* voisin_NO(Type_Case c)
{
	return c.NO;
}

Type_Case* voisin_NE(Type_Case c)
{
	return c.NE;
}

Type_Case* voisin_O(Type_Case c)
{
	return c.O;
}

Type_Case* voisin_E(Type_Case c)
{
	return c.E;
}

Type_Case* voisin_SO(Type_Case c)
{
	return c.SO;
}

Type_Case* voisin_SE(Type_Case c)
{
	return c.SE;
}