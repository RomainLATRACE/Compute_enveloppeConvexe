#include "filedatamanager.h"

FileDataManager::FileDataManager(string nomFichier){
	nom = nomFichier;
}

vector<Point> FileDataManager::lireFichier(){
	// Ouverture d'un flux pour le fichier
	ifstream input(nom.c_str());
	
	// Test si le flux est bien créé
	if(!input){
		// Si non
		cout << "Création du flux échoué !" << endl;
		exit(0);
	// Si oui 
	}else cout << "Fichier " << nom << " connecté" << endl;			
	
	// Déclaration du tableu de point à retourner
	vector<Point> points;
	// Déclaration des variables pour la lecture des données et son traitement
	string ligne;
	string strTab[2];
	
	// Boucle qui li le fichier depuis le flux
	while(getline(input,ligne)){
		// Récupère l'index de l'espace dans la chaîne de caractères
		int index = ligne.find(' ');
		// Met le premier nombre lu dans la première case du tableau
		strTab[0] = ligne.substr(0,index);
		// Met le deuxième nombre lu dans la deuxième case du tableau
		strTab[1] = ligne.substr(index+1,ligne.length());
		// Ajout dans le tableau d'un nouveau point avec les valeurs récupérer converties en nombres
		points.push_back(Point(atof(strTab[0].c_str()),atof(strTab[1].c_str())));
	}
	
	// Fermeture du flux
	input.close();
	// Retourne le tableau de points créé
	return points;
}
	

bool FileDataManager::ecrireFichier(vector<Point> points){
	return 1;
}

/*void FileDataManager::fermerFichier(){
	input.close();
	output.close();
}*/
