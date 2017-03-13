/*
 * TurnOn.cpp
 *
 *  Created on: Nov 26, 2016
 *      Author: peng81
 */

#include "TurnOn.h"

TurnOn::TurnOn(xml_node<>* xnode) {
	// TODO Auto-generated constructor stub
	initialize(xnode);

}

TurnOn::~TurnOn() {
	// TODO Auto-generated destructor stub
}

void TurnOn::initialize(xml_node<>* xnode){
	for (xml_node<>* curr = xnode->first_node(); curr; curr = curr->next_sibling()){
		if (string(curr->name()) == "print"){
			print = curr->value();
			//cout << "TurnOn print: " << print << endl;
		}else if (string(curr->name()) == "action"){
			action = curr->value();
			//cout << "TurnOn action: " << action << endl;
		}
	}
}
