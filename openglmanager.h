#ifndef OPENGLMANAGER_H
#define OPENGLMANAGER_H

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <string>
#include <vector>

#include "point.h"
#include "callbacks.h"

class OpenGLManager {
	
	private:
	
	public:
	
	OpenGLManager(int argc, char *argv[]);
	void creerFenetre(string titre, GLushort largeur, GLushort hauteur);
	void initOpenGL();
	void initialisation(vector<Point> points);
	void lancementOpenGL();
	
	static void creerPoint(Point p, double rouge, double vert, double bleu, double taille);
	static void creerSegment(Point p1, Point p2, double rouge, double vert, double bleu, double taille);
	static void ajouterPoint(Point p);
//	static void supprimerPoint();
	static void afficherListeDePoint(vector<Point> points);
};

#endif
