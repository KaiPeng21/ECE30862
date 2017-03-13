//============================================================================
// Name        : Zork.cpp
// Author      : Peng
// Version     :
// Copyright   : 
// Description : Purdue ECE 30862
//============================================================================

#include <iostream>
#include "ZorkGame.h"

/* import XML parser libraries */


using namespace std;
using namespace rapidxml;

int main(int argc, char *argv[]) {
	cout << "Zork Project" << endl; // prints Zork Project

	if (argc < 2){
		cout << "Error: Insufficient argument!";
		return 1;
	}

	file<> xmlFile(argv[1]);
	xml_document<> doc;
	doc.parse<0>(xmlFile.data());

	xml_node<> *mapnode = doc.first_node();

	ZorkGame *g = new ZorkGame(&mapnode);
	g->startGame();

	delete g;

	return 0;
}
