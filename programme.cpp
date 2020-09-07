#include "programme.h"

bool enveloppeAffiche = false;
bool pointsEnveloppeAffiche = false;

Programme::Programme(int argc, char *argv[]){
	this->argc = argc;
	this->argv = argv;
	
	for(int i=0; i<argc; i++)
		parametres.push_back(string(argv[i]));
		
	if (argc >2)  {
        cout << "Usage : " << argv[0] << " nom_fichier\n";
        exit(1);
    }else if (argc == 2){
		chargementPointsFichier(parametres[1]);
	}
	delPress = false;
	adPress = false;
}

void Programme::setGraphique(Graphique *g){
	graphique = g;
}

void Programme::menuChargementPoints(){
	int choix;
	bool invalide = true;
	cout << "Chargement des points." << endl << "----------------------" << endl;
	cout << "1- Depuis un fichier" << endl;
	cout << "2- Aléatoirement" << endl;
	cout << "3- Manuellement en tappant les valeurs" << endl;
	cout << "0- Annuler et fermer" << endl;
	
	while(invalide){
		invalide = false;
		cout << "Quel solution de chargement de point voulez vous utiliser ? " ;
		cin >> choix;
		
		switch(choix){
			case 0:
				quitter();
				break;
			case 1:
				chargementPointsFichier();
				break;
			case 2:
				chargementPointsAleatoire();
				break;
			case 3:
				chargementPointsManuel();
				break;
			default:
				cout << "Le choix n'est pas valide" << endl;
				invalide = true;
				break;
		}
	} 
}

void Programme::chargementPointsFichier(){
	string nom;
	cout << "Quel est le nom du fichier ? ";
	cin >> nom;
	chargementPointsFichier(nom);
}

void Programme::chargementPointsFichier(string nomFichier){
	FileDataManager fdm(nomFichier);
	points = fdm.lireFichier();
	cout << "Chargement depuis le fichier : " << nomFichier << endl;
}

void Programme::chargementPointsAleatoire(){
	int nbPoints, precision;
	int min, max;
	
	cout << "Combien voulez-vous ajouter de points ? ";
	cin >> nbPoints;
	cout << "Entre combien et combien ? Tapez le nombre min puis le nombre max : ";
	cin >> min >> max;
	cout << "Avec quelle précision, combien de chiffre après la virgule ? ";
	cin >> precision;
	chargementPointsAleatoire(nbPoints,min,max,precision);
}

void Programme::chargementPointsAleatoire(int nbPoints,int min,int max,int precision){
	if(max < min)
		swap(min,max);
	
	for(int i = 0; i < nbPoints; i++)
		points.push_back(Point(min,max,precision));
}

void Programme::chargementPointsManuel(){
	double x, y;
	Point *p;
	cout << "Ajouter un point (ou Ctrl + D pour arrêter) : ";
	while(cin >> x >> y){
		//cout << "eof : " << cin.eof() << endl;
		p = new Point(x,y);
		points.push_back(*p);
		cout << "Point " << *p << " ajouté, nouveau : ";
	}
	cin.clear();
}

void Programme::afficherChoix(){
	cout << "==============================================" << endl;
	//cout << endl /*<< (char)201*/ << "================" /*<< (char)187*/ << endl /*<< (char)186*/ << " Menu principal " /*<< (char)186*/ << endl /*<< (char) 200*/ <<"================" /*<< (char) 188*/ << endl;
	cout << "Q- Pour quitter l'application" << endl;
	cout << "C- Pour centrer le graphe" << endl;
	cout << "E- Pour calculer l'enveloppe convexe du graphe" << endl;
	cout << "R- Enlever/Remettre enveloppe convexe" << endl;
	cout << "T- Enlever/Remettre les points de l'enveloppe" << endl;
	//cout << "A- Pour ajouter des points au graphe" << endl;
	//cout << "S- Pour supprimer des points du graphe" << endl;
	cout << "- ou + pour modifier le zoom" << endl;
	cout << "4, 6, 2, 8 ou les touches flêchées pour se déplacer" << endl;
}

void Programme::menuPrincipal(char choix){
	//cout << "choix : " << choix << endl;
	switch(choix){
		case 'E' : case 'e' :
			menuCalculerEnveloppeConvexe();
			break;
		case 'Q' : case 'q' :
			quitter();
			break;
		case 'C' : case 'c' :
			centrer();
			break;
		case 'R' : case 'r' :
			gestionEnveloppeConvexe();
			break;
		case 'T' : case 't' :
			gestionPointsEnveloppeConvexe();
			break;
		/*case 'A' : case 'a' :
			ajouterPoints();
			break;*/
		/*case 'S' : case 's' :
			//supprimerPoints();
			break;*/
		case '+' : zoomIn(); break;
		case '-' : zoomOut(); break;
		case '6' : translateXMoins();  break;
		case '4' : translateXPlus();  break;
		case '8' : translateYMoins();  break;
		case '2' : translateYPlus();  break;
		default:
			cout << "Le choix n'est pas valide" << endl;
			break;
	}
}

void Programme::quitter(){
	cout << "Fermeture de l'application" << endl;
	exit(0);
}

void Programme::menuCalculerEnveloppeConvexe(){
	int choix;
	bool invalide = true;
	
	cout << "Calcul de l'enveloppe convexe." << endl << "------------------------------" << endl;
	cout << "1- Marche de Jarvis" << endl;
	cout << "2- Algorithme Graham" << endl;
	cout << "3- Quick hull" << endl;
	cout << "0- Annuler et fermer" << endl;
	
	while(invalide){
		invalide = false;
		cout << "Quel solution de chargement de point voulez vous utiliser ? " ;
		cin >> choix;
		
		switch(choix){
			case 0:
				//quitter();
				return;
				break;
			case 1:
			case 2:
			case 3:
				enveloppe = calculerEnveloppeConvexe(choix);
				break;
			default:
				cout << "Le choix n'est pas valide" << endl;
				invalide = true;
				break;
		}
	} 
	
	//double duree;// = double(fin - debut)/CLOCKS_PER_SEC;
	/*cout << "Temps pour réaliser l'algorithme et obtenir l'enveloppe : "; //<< duree << " milli-secondes." << endl; 
	if(duree < 1){
		duree * 1000;
		printf("%f milli-secondes", duree);
	}else if(duree < 0.001){
		duree * 1000000;
		printf("%f micro-secondes", duree);
	}else printf("%f secondes", duree);
	cout << endl;*/
	
	cout << "Les points de l'enveloppe sont : " << endl;
	for(vector<Point>::iterator it = enveloppe.begin(); it != enveloppe.end(); ++it)
		cout << *it << endl;
	
	afficherEnvelopperConvexe();
	enveloppeAffiche = true;
}

void Programme::gestionEnveloppeConvexe(){
	if(enveloppe.empty()) return;
	
	if(enveloppeAffiche){
		glNewList(4,GL_COMPILE_AND_EXECUTE);
		glEndList();
		affichage();		
		enveloppeAffiche = false;
	}
	else {
		afficherEnvelopperConvexe();
		enveloppeAffiche = true;
	}
}

void Programme::gestionPointsEnveloppeConvexe(){
	if(enveloppe.empty()) return;
	
	if(pointsEnveloppeAffiche){
		OpenGLManager::afficherListeDePoint(enveloppe);
		pointsEnveloppeAffiche = false;
	}
	else {
		OpenGLManager::afficherListeDePoint(points);
		pointsEnveloppeAffiche = true;
	}
}

vector<Point> Programme::calculerEnveloppeConvexe(int choix){
	//usleep(5000000);
	switch(choix){
		case 1:
			return CalculEnveloppeConvexe::marcheJarvis(points);
		case 2:
			return CalculEnveloppeConvexe::algoGraham(points);
		case 3:
			return CalculEnveloppeConvexe::quickHull(points);
	}
}

void Programme::ajouterPoints(){
	/*if(!adPress){
		adPress = true;
		cout << "Appuyer sur A pour arrêter l'ajout de points." << endl;
		cout << "Clique gauche de la souris pour ajouter un point" << endl;		
	}else adPress = false;
	
	cout << adPress << endl;*/
	chargementPointsManuel();
	affichage();
}
