#ifndef POINT_H
#define POINT_H

#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <cmath>

#define PI 3.14159265

using namespace std;

// La classe Point
class Point{

	private :
	// Coordonnée x
	double x;
	// Coordonnée y
	double y;
	
	public :
	// Accesseur x
	double getX();
	// Mutateur x
	void setX(double X);
	
	// Accesseur y
	double getY();
	// Mutateur y
	void setY(double Y);
	
	// Constructeur prenant la valeur x, y
	Point(double X, double Y);
	// Constructeur permettant de générer aléatoirement un point suivant des valeurs
	Point(int min, int max, int precision);
	
	/* Quant le point est dans la pile */
	friend ostream& operator<<(ostream &o, const Point &P);
	/* Quant le point est dans le tas */
	friend ostream& operator<<(ostream &o, const Point *P);
	
	// Surcharge opérateur de comparaison inférieur
	bool operator < (Point &p);
	bool operator < (Point *p);
	// Surcharge opérateur d'égalité
	bool operator == (Point &p);
	bool operator == (Point *p);
	// Surcharge opérateur de différence
	bool operator != (Point &p);
	bool operator != (Point *p);
	
	// Fonction de distance à un autre point
	double distance(Point p);
	
	// Fonctions static 
	// Calcul l'angle polaire entre 3 points
	static bool anglePolaire(Point pivot, Point p1,Point p2);
	// Calcul de l'angle horaire entre 3 points
	static int angleHoraire(Point p1, Point p2, Point p3);
	// Calcul de l'angle en degrés entre 3 points
	static int angle(Point p1, Point p2, Point p3);
	// Permet de calcul la distance d'un point à un segment perpendiculairement
	static double distancePointSegment(Point P, Point A, Point B);
};

// La classe PointComparateur 
// Utile uniquement pour le trie par rapport à un point pivot
class PointComparateur {
	// Le pivot nécessaire à la comparaison
	Point *pivot;
	
	public:
	// Constructeur
	PointComparateur(double x, double y){
		pivot = new Point(x,y);
	}
	
	// Surcharge de l'opérateur utile à la comparaison
	bool operator()(Point p1,Point p2){
		return Point::anglePolaire(*pivot,p1,p2);
	}
};

#endif
