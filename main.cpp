#include <stdlib.h>
#include <stdio.h>

#include "programme.h"
#include "openglmanager.h"

using namespace std;

// Valeurs prédéfinit taille de la fenêtre
GLushort largeur_fenetre = 600;
GLushort hauteur_fenetre = 600;


Programme *prog;

int main(int argc, char *argv[]){
	// Instanciation d'un programme
	prog = new Programme(argc, argv);
	
	// Si la liste des points est vide il faut la remplir
	if(prog->points.empty())
		prog->menuChargementPoints();
		
	cout << "Voici les points chargés :" << endl;
	for(vector<Point>::iterator it = prog->points.begin(); it != prog->points.end(); ++it)
		cout << *it << endl;
		
	// Instanciation de la classe graphique
	// Permettant de récuperer des informations sur l'ensemble de points
	Graphique *graph;
	graph = new Graphique(prog->points);
		
	// Instanciation de la classe qui va manipuler OpenGL
	OpenGLManager openGL(argc, argv);
	openGL.creerFenetre("Enveloppe convexe",largeur_fenetre,hauteur_fenetre);
	openGL.initOpenGL();
	openGL.initialisation(prog->points);
	openGL.lancementOpenGL();
				
	return 0;
}
