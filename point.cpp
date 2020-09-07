#include "point.h"

double Point::getX(){
	return x;
}
void Point::setX(double X){
	x = X;
}

double Point::getY(){
	return y;
}
void Point::setY(double Y){
	y = Y;
}

Point::Point(double X, double Y){
	setX(X);
	setY(Y);
}

// Fonction fénérant un point aléatoire
Point::Point(int min, int max, int precision){
	int maxVirgule = 1, minVirgule = 0, xVirgule, yVirgule, x, y;
	
	// initialise le nombre correspondant à precision puissance de 10
	for(int i = 0; i < precision; i++)
		maxVirgule *= 10;
		
	// génère le futur nombre compris entre 0 et 1 avec precision chiffre.
	xVirgule = rand() % (maxVirgule - minVirgule) + minVirgule;
	yVirgule = rand() % (maxVirgule - minVirgule) + minVirgule;
	
	// génère le nombre entier
	x = rand() % (max - min) + min;
	y = rand() % (max - min) + min;
	
	// set les coordonnées en additionnant l'entier avec le nombre entre 0 et 1
	setX(x + (double)xVirgule/maxVirgule);
	setY(y + (double)yVirgule/maxVirgule);
}

ostream& operator<<( ostream &o, const Point &P) {
	o << "{" << P.x << ";" << P.y << "}";
	return o;
}

ostream& operator<<( ostream &o, const Point *P) {
	o << "{" << P->x << ";" << P->y << "}";
	return o;
}

bool Point::operator< (Point &p){
	if(getY() != p.getY())
		return getY() < p.getY();
	else return getX() < p.getX();
}

bool Point::operator < (Point *p){
	if(getY() != p->getY())
		return getY() < p->getY();
	else return getX() < p->getX();
}

bool Point::operator== (Point &p){
	return getX() == p.getX() && getY() == p.getY();
}

bool Point::operator== (Point *p){
	return getX() == p->getX() && getY() == p->getY();
}

bool Point::operator!= (Point &p){
	return !(*this == p);
}

bool Point::operator!= (Point *p){
	return !(*this == p);
}

double Point::distance(Point p){
	double dx = getX() - p.getX();
	double dy = getY() - p.getY();
	return dx * dx + dy * dy;
}

bool Point::anglePolaire(Point pivot, Point p1, Point p2){
	double order = Point::angleHoraire(pivot,p1,p2);
	if(order == 0)
		return pivot.distance(p1) < pivot.distance(p2);
	else return order == -1;
}

int Point::angleHoraire(Point p1, Point p2, Point p3){
	double area = (p2.getX() - p1.getX()) * (p3.getY() - p1.getY()) - (p2.getY() - p1.getY()) * (p3.getX() - p1.getX());
	if(area > 0)
		return 1;
	else if(area < 0)
		return -1;
	else return 0;
}

int Point::angle(Point p1, Point p2, Point p3){
	Point p12(p2.getX() - p1.getX(), p2.getY() - p1.getY());
	Point p32(p2.getX() - p3.getX(), p2.getY() - p3.getY());
	
	float dot = (p12.getX() * p32.getX() + p12.getY() * p32.getY());
	float cross = (p12.getX() * p32.getY() - p12.getY() * p32.getX());
	float alpha = atan2(cross, dot);
	
	int angle = (int) floor(alpha * 180. / PI + 0.5);
	angle = (angle < 0)? angle + 360 : angle;
	//if(angle < 0) angle *= -1;
	//cout << p1 << " " << p2 << " " << p3 << " angle : " << angle << endl;
	return angle;
}

double Point::distancePointSegment(Point P, Point A, Point B){
	return (P.getX() - A.getX())*(B.getY()-A.getY())-((P.getY() - A.getY())*(B.getX() - A.getX()));
}
