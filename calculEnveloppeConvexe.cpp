#include "calculEnveloppeConvexe.h"

vector<Point> CalculEnveloppeConvexe::algoGraham(vector<Point> points){	
	vector<Point> enveloppe;
	
	if(points.size() < 3)
		return points;
		
	int yMinim = 0, i = 0;
	Point pivot = points.front();
	for(vector<Point>::iterator it = points.begin(); it != points.end(); ++it){
		if(*it < pivot){
			pivot = *it;
			yMinim = i;
		}
		i++;
	}
	
	swap(points[0],points.at(yMinim));
	
	sort(points.begin() + 1, points.end(), PointComparateur(pivot.getX(),pivot.getY()));
	
	enveloppe.push_back(points[0]);
	enveloppe.push_back(points[1]);
	enveloppe.push_back(points[2]);
	
	for(vector<Point>::iterator it = points.begin() + 3; it != points.end(); ++it){
		Point top = enveloppe.back();
		enveloppe.pop_back();
		while(Point::angleHoraire(enveloppe.back(), top, *it) > -1){
			top = enveloppe.back();
			enveloppe.pop_back();
		}
		enveloppe.push_back(top);
		enveloppe.push_back(*it);
	}	

	return enveloppe;
}

vector<Point> CalculEnveloppeConvexe::marcheJarvis(vector<Point> points){
	vector<Point> enveloppe;
	
	if(points.size() < 3)
		return points;
		
	Point pivot = points.front();
	int yMinim = 0, i = 0;
	for(vector<Point>::iterator it = points.begin(); it != points.end(); ++it){
		if(*it < pivot){
			pivot = *it;
		}
	}
	
	Point p = pivot, last = Point(pivot.getX(),pivot.getY()-10), current = pivot;
	int meilleurAngle, angle;
	i =0;
	
	do{
		//cout << p << endl;
		enveloppe.push_back(p);
		meilleurAngle = 0;
		for(vector<Point>::iterator it = points.begin(); it != points.end(); ++it){
			if(*it == p) continue;
			angle = Point::angle(last,p,*it);
			if(angle > meilleurAngle){
				meilleurAngle = angle;
				current = *it;
			}
		}	
		last = p;
		p = current;
	}while(p != pivot);
	
	return enveloppe;
}

vector<Point> CalculEnveloppeConvexe::quickHull(vector<Point> points){
	vector<Point> enveloppe, dessus, dessous;
	Graphique graphique(points);
	
	Point gauche = graphique.pointLePlusAGauche();
	Point droit = graphique.pointLePlusADroite();
	enveloppe.push_back(gauche);
	float distance;
	
	for(vector<Point>::iterator it = points.begin(); it != points.end(); ++it){
		if(*it != gauche && *it != droit){
			distance = Point::distancePointSegment(*it,gauche,droit);
			if(distance > 0)
				dessous.push_back(*it);
			else if(distance < 0) dessus.push_back(*it);
		}
	}
	
	quickHullRecursive(dessous, gauche, droit, enveloppe);	
	enveloppe.push_back(droit);
	quickHullRecursive(dessus, droit, gauche, enveloppe);
	
	return enveloppe;
}

void CalculEnveloppeConvexe::quickHullRecursive(vector<Point> points, Point P, Point Q, vector<Point>& enveloppe){
	if(points.empty()) return;
	
	float plusLoin = 0, distance;
	Point C = points.at(0);
	vector<Point> s1, s2;
	
	for(vector<Point>::iterator it = points.begin(); it != points.end(); ++it){
		distance = Point::distancePointSegment(*it,P,Q);
		if(distance > plusLoin){
			plusLoin = distance;
			C = *it;
		}
	}
	
	for(vector<Point>::iterator it = points.begin(); it != points.end(); ++it){
		if(*it != P && *it != Q){
			if(Point::distancePointSegment(*it,P,C) > 0)
				s1.push_back(*it);
			else if(Point::distancePointSegment(*it,C,Q) > 0)
				s2.push_back(*it);
		}
	}
	
	quickHullRecursive(s1, P, C, enveloppe);
	enveloppe.push_back(C);
	quickHullRecursive(s2, C, Q, enveloppe);	
}
