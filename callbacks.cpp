#include "callbacks.h"

int anglex, angley, x, y, xold, yold;
char presse;
double Scal=35, trX=0.0,trY=0.0,dist=0.;//,trZ=0.0
//double Scal, trX, trY, dist;//,trZ=0.0
float pasZoom = 0.5, pasTranslation = 0.2;

extern Programme *prog;

void centrer(){
	Graphique graphique(prog->points);
	int width = 0, height = 0;
	width = glutGet(GLUT_WINDOW_WIDTH);
	height = glutGet(GLUT_WINDOW_HEIGHT);

	double widthRatio, heightRatio, distGD, distBH;

	distGD = graphique.distanceGaucheADroite();
	distBH = graphique.distanceBasEnHaut();
	widthRatio = (width/distGD)*0.9;
	heightRatio = (height/distBH)*0.9;

	int valZoom;
	if(widthRatio < heightRatio)
		valZoom = widthRatio;
	else valZoom = heightRatio;
	valZoom/=2;
	dist = valZoom;
	Scal = valZoom;

	Point centre = graphique.centre();
	trX = centre.getX() * 1;
	trY = centre.getY() * -1;

	glutPostRedisplay();
}

void affichage()
{
  // effacement de l'image avec la couleur de fond
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();

  glTranslatef(0.0,0.0,dist);

 // Pour la 2D
  glRotatef(-anglex+angley,0.0,0.0,1.0);
  glScalef(Scal,Scal,Scal); // diminution de la vue de la scene
  glRotatef(180,0.0,1.0,0.0);
  glRotatef(180,1.0,0.0,0.0);
  glTranslatef(-trX,trY,0.);
      glCallList(1); // appel de la liste numero 1
      glCallList(2);   // appel de la liste numero 2
      glCallList(3);   // appel de la liste numero 3
      glCallList(4);
  glFlush();
  // On echange les buffers
  glutSwapBuffers();
}

void reshape(int x,int y)
{
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  //taille de la scene
  double  Ortho=-150;
  glOrtho(-Ortho,Ortho,-Ortho,Ortho,-Ortho,Ortho);// fenetre
  glMatrixMode(GL_MODELVIEW);
  glViewport(0,0,x,y);
}

void clavier(unsigned char touche,int x,int y)
{
	prog->menuPrincipal(touche);
}

void clavierSpecial(int key, int x, int y){
	switch(key){
		case GLUT_KEY_RIGHT : trX-=pasTranslation;  glutPostRedisplay();  break;
		case GLUT_KEY_LEFT : trX+=pasTranslation;  glutPostRedisplay();  break;
		case GLUT_KEY_UP : trY+=pasTranslation;  glutPostRedisplay();  break;
		case GLUT_KEY_DOWN : trY-=pasTranslation;  glutPostRedisplay();  break;
		//default : printf("%d \n",key);
	}
}

void zoomIn(){
	dist+= pasZoom;
	Scal += pasZoom;
	glutPostRedisplay();
}

void zoomOut(){
	dist-= pasZoom;
	Scal-=pasZoom;
	glutPostRedisplay();
}

void translateXMoins(){
	trX-=pasTranslation;
	glutPostRedisplay();
}

void translateXPlus(){
	trX+=pasTranslation;
	glutPostRedisplay();
}

void translateYMoins(){
	trY-=pasTranslation;
	glutPostRedisplay();
}

void translateYPlus(){
	trY+=pasTranslation;
	glutPostRedisplay();
}

void mouse(int button, int state,int x,int y)
{
	// si on appuie sur le bouton gauche
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if(prog->adPress){
			//cout << "Ajout du point : " << windowPositionToPoint(x,y) << endl;
			prog->points.push_back(windowPositionToPoint(x,y));
			OpenGLManager::afficherListeDePoint(prog->points);
		}else{
			xold = x; // on sauvegarde la position de la souris
			yold=y;
			presse = 1; // le booleen presse passe a 1 (vrai)
		}
	}
	// si on relache le bouton gauche
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
		presse=0; // le booleen presse passe a 0 (faux)
}

void mousemotion(int x,int y)
{
	if(prog->adPress){

	}else if (presse) // si le bouton gauche est presse
    {
		// on modifie les angles de rotation de l'objet
		// en fonction de la position actuelle de la souris et de la derniere
		// position sauvegardee
		anglex=anglex+(x-xold);
		angley=angley+(y-yold);
		glutPostRedisplay(); // on demande un rafraichissement de l'affichage
    }

    xold=x; // sauvegarde des valeurs courante de le position de la souris
    yold=y;
}

void passivemousemotion(int x, int y){
	if(prog->adPress){
	/*	Point p(x,y);
		ostringstream os;
		os << p;
		string position = os.str();
		glColor3f(1.,0.,0.);
		glRasterPos2i(x,y);
		for(int i = 0; i < position.size(); i++){
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, position[i]);
			cout << position[i];
		}
		glutPostRedisplay();*/
	}
}

void afficherEnvelopperConvexe(){
	vector<Point> enveloppe = prog->enveloppe;
	glNewList(4,GL_COMPILE_AND_EXECUTE);
	for(vector<Point>::iterator it = enveloppe.begin(); it != enveloppe.end();){
		Point p1 = *it, p2 = *++it;
		if(it == enveloppe.end())
			p2 = *enveloppe.begin();

		// Tracer le segment de l'enveloppe convexe
		OpenGLManager::creerSegment(p1,p2,1.0,0.0,1.0,2.0);
	}
	glEndList();
	affichage();
}

Point windowPositionToPoint(int x,int y){
	double X = x - glutGet(GLUT_WINDOW_WIDTH)/2 - trX;
	double Y = y - glutGet(GLUT_WINDOW_HEIGHT)/2 - trY;

	X /= Scal;
	Y /= Scal;

	//Y = -Y;

	cout << X << " " << Y << endl;

	return Point(X,Y);
}
