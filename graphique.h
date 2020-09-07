#ifndef GRAPHIQUE_H
#define GRAPHIQUE_H

#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

#include "point.h"

using namespace std;

class Graphique{
	
	private:
	
	vector<Point> points;
	
	public:
	
	Graphique(vector<Point> nuage);
	
	Point pointLePlusAGauche();
	Point pointLePlusADroite();
	Point pointLePlusBas();
	Point pointLePlusHaut();
	
	double distanceGaucheADroite();
	double distanceBasEnHaut();
	
	Point centre();
};

#endif
