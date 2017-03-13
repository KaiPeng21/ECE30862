/*
 * CreatureAttack.cpp
 *
 *  Created on: Nov 26, 2016
 *      Author: peng81
 */

#include "CreatureAttack.h"

CreatureAttack::CreatureAttack(xml_node<>* xnode) {
	// TODO Auto-generated constructor stub
	initialize(xnode);
}

CreatureAttack::~CreatureAttack() {
	// TODO Auto-generated destructor stub
}

void CreatureAttack::initialize(xml_node<>* xnode){
	print = "nothing to print";

	for (xml_node<> * curr = xnode->first_node(); curr; curr = curr->next_sibling()){
		if (string(curr->name()) == "condition"){
			condition = new AttackCondition(curr);
		}else if (string(curr->name()) == "print"){
			print = curr->value();
		}else if (string(curr->name()) == "action"){
			action.push_back(curr->value());
		}
	}
}
