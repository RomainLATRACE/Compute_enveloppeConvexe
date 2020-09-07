#ifndef CALLBACKS_H
#define CALLBACKS_H

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

#include "point.h"
#include "programme.h"
#include "graphique.h"

using namespace std;

void centrer();
void affichage();
void reshape(int x,int y);
void clavier(unsigned char touche,int x,int y);
void clavierSpecial(int key, int x, int y);
void mouse(int button, int state,int x,int y);
void passivemousemotion(int x,int y);
void mousemotion(int x,int y);
void afficherEnvelopperConvexe();

void zoomIn();
void zoomOut();
void translateXMoins();
void translateXPlus();
void translateYMoins();
void translateYPlus();

Point windowPositionToPoint(int x,int y);

#endif
