/*
 * Border.cpp
 *
 *  Created on: Nov 26, 2016
 *      Author: peng81
 */

#include "Border.h"

Border::Border(xml_node<>* xnode) {
	// TODO Auto-generated constructor stub
	initialize(xnode);
}

Border::~Border() {
	// TODO Auto-generated destructor stub
}

void Border::initialize(xml_node<>* xnode){
	for (xml_node<>* curr = xnode->first_node(); curr; curr = curr->next_sibling()){
		if (string(curr->name()) == "name"){
			name = curr->value();
		}
		else if (string(curr->name()) == "direction"){
			direction = curr->value();
		}
	}

	/*
	cout << "border name and direction:" << endl;
	cout << name << endl;
	cout << direction << endl;
	*/
}
