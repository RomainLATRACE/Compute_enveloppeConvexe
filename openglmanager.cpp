#include "openglmanager.h"

extern Programme *prog;

OpenGLManager::OpenGLManager(int argc, char *argv[]){
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
}

void OpenGLManager::creerFenetre(string titre, GLushort largeur, GLushort hauteur){
	glutInitWindowPosition(100,100);
	glutInitWindowSize(largeur,hauteur);
	glutCreateWindow(titre.c_str());
}

void OpenGLManager::initOpenGL(){
	glClearColor(1.0,1.0,1.0,0.0);
	glColor3f(0.0,0.0,0.0);
	glPointSize(0.5);
	glEnable(GL_DEPTH_TEST);
	glColor3f(0.0,0.0,0.0);
	glEdgeFlag(GL_TRUE);
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER,GL_TRUE);
	glDisable(GL_LIGHTING);
}

void OpenGLManager::lancementOpenGL(){
	// Assignation des fonctions de gestion au évènement OpenGL
	glutDisplayFunc(affichage);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);
	glutMotionFunc(mousemotion);
	glutPassiveMotionFunc(passivemousemotion);
	glutKeyboardFunc(clavier);
	glutSpecialFunc(clavierSpecial);
	
	// Boucle pour l'application graphique
	centrer();
	prog->afficherChoix();
	glutMainLoop();
}

void OpenGLManager::initialisation(vector<Point> points){ 
	Point O(0.,0.), I(1.,0.), J(0.,1.);
	glNewList(1,GL_COMPILE_AND_EXECUTE); //liste numero 1
		creerPoint(O,1.,0.,0.,8.); //O
		creerPoint(J,0.,0.5,0.,8.); //J
		creerPoint(I,0.,0.,1.,8.);//I
	glEndList();
	glNewList(2,GL_COMPILE_AND_EXECUTE);  //liste numero 2
		creerSegment(O,I,1.0,0.0,1.0,2.0); // on trace [OI]
		creerSegment(O,J,1.0,0.50,0.0,2.0);// on trace [OJ]
	glEndList();
	afficherListeDePoint(points);
}

void OpenGLManager::creerPoint(Point p, double rouge, double vert, double bleu, double taille){
	glColor3f(rouge,vert,bleu);	//initialisation de la couleur
	glPointSize(taille);	// initialisation de la taille
	glBegin(GL_POINTS);	// on trace un point
		glVertex2f(p.getX(),p.getY());	// coordonnees du point
	glEnd();	// fin de glBegin
}

void OpenGLManager::creerSegment(Point p1, Point p2, double rouge, double vert, double bleu, double taille){
	glColor3f(rouge,vert,bleu);//initialisation de la couleur
	glLineWidth(taille); // initialisation de la taille
	glBegin(GL_LINES); // on trace un segment
		glVertex2f(p1.getX(),p1.getY()); // coordonnees du premier point
		glVertex2f(p2.getX(),p2.getY()); // coordonnees du dernier point 
	glEnd(); // fin de glBegin
}

void OpenGLManager::afficherListeDePoint(vector<Point> points){
	// Création de la liste des points récupérés
	glNewList(3,GL_COMPILE_AND_EXECUTE);
		// Parcours du tableau de points
		for(vector<Point>::iterator it = points.begin(); it != points.end(); ++it)
			// Création du point graphique
			creerPoint(*it,0.,0.,0.,8.);
	glEndList();
	affichage();
}
