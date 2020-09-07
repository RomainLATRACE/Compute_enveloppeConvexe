#ifndef PROGRAMME_H
#define PROGRAMME_H

#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <time.h>

#include "point.h"
#include "filedatamanager.h"
#include "graphique.h"
#include "openglmanager.h"
#include "callbacks.h"
#include "calculEnveloppeConvexe.h"

using namespace std;

class Programme {
	
	private:
	Graphique *graphique;
	
	public:
	int argc;
	char **argv;
	vector<string> parametres;
	vector<Point> points;
	vector<Point> enveloppe;
	//bool adPress = false, delPress = false;
	bool adPress, delPress;
	
	Programme(int argc, char *argv[]);
	void setGraphique(Graphique *g);
	
	void menuChargementPoints();
	void chargementPointsFichier();
	void chargementPointsFichier(string nomFichier);
	void chargementPointsAleatoire();
	void chargementPointsAleatoire(int nbPoints,int min,int max,int precision);
	void chargementPointsManuel();
	
	void afficherChoix();
	void quitter();
	
	void menuPrincipal(char choix);
	
	void menuCalculerEnveloppeConvexe();
	vector<Point> calculerEnveloppeConvexe(int choix);
	
	void gestionEnveloppeConvexe();
	void gestionPointsEnveloppeConvexe();
	
	void ajouterPoints();
};

#endif
