#ifndef CALCULENVELOPPECONVEXE_H
#define CALCULENVELOPPECONVEXE_H

#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

#include <bits/stdc++.h>
#include <algorithm>
#include <functional>

#include "point.h"
#include "graphique.h"

using namespace std;

class CalculEnveloppeConvexe {
	
	protected:
	static Graphique graphique;
	
	public:
	static vector<Point> algoGraham(vector<Point> points);
	static vector<Point> marcheJarvis(vector<Point> points);
	static vector<Point> quickHull(vector<Point> points);
	
	private:
	static void quickHullRecursive(vector<Point> points, Point P, Point Q, vector<Point>& enveloppe);
};

#endif
