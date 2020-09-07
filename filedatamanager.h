#ifndef FILEDATAMANAGER_H
#define FILEDATAMANAGER_H

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <sstream>
#include <vector>

#include "point.h"
 
using namespace std;

class FileDataManager{
	
	private :
	string nom;
	/*ifstream input;
	ofstream output;*/
	
	public:	
	// Constructeur
	FileDataManager(string nomFichier);
	// Lire les points dans un fichier
	vector<Point> lireFichier();
	// Ecrire les points dans un fichier
	bool ecrireFichier(vector<Point> points);
	// Fermer le fichier ouvert
	//void fermerFichier();	
};

#endif
