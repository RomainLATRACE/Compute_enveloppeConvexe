#include "graphique.h"


Graphique::Graphique(vector<Point> nuage){
	points = nuage;
}

Point Graphique::pointLePlusAGauche(){
	Point p = points[0];

	for(vector<Point>::iterator i = points.begin(); i != points.end(); ++i)
		if(i->getX() < p.getX() || (i->getX() == p.getX() && i->getY() < p.getY()))
			p = *i;

	return p;
}

Point Graphique::pointLePlusADroite(){
	Point p = points[0];
	double x;
	for(vector<Point>::iterator i = points.begin(); i != points.end(); ++i)
		if(i->getX() > p.getX() || (i->getX() == p.getX() && i->getY() > p.getY())){
			p = *i;
		}

	return p;
}

Point Graphique::pointLePlusBas(){
	Point p = points[0];
	
	for(vector<Point>::iterator i = points.begin(); i != points.end(); ++i)
		if(i->getY() < p.getY() || (i->getY() == p.getY() && i->getX() < p.getX()))
			p = *i;

	return p;
}

Point Graphique::pointLePlusHaut(){
	Point p = points[0];
	
	for(vector<Point>::iterator i = points.begin(); i != points.end(); ++i)
		if(i->getY() > p.getY() || (i->getY() == p.getY() && i->getX() > p.getX()))
			p = *i;

	return p;
}

double Graphique::distanceGaucheADroite(){
	return pointLePlusADroite().getX() - pointLePlusAGauche().getX();
}

double Graphique::distanceBasEnHaut(){
	return pointLePlusHaut().getY() - pointLePlusBas().getY();
}

Point Graphique::centre(){
	double x, y;
	x = distanceGaucheADroite()/2.0;
	y = distanceBasEnHaut()/2.0;
	return Point(pointLePlusAGauche().getX() + x,pointLePlusBas().getY() + y);
}
