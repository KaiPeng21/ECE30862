/*
 * Creature.cpp
 *
 *  Created on: Nov 20, 2016
 *      Author: peng81
 */

#include "Creature.h"

Creature::Creature(xml_node<>* xnode) {
	// TODO Auto-generated constructor stub
	initialize(xnode);

}

Creature::~Creature() {
	// TODO Auto-generated destructor stub
}

void Creature::initialize(xml_node<>* xnode){
	for (xml_node<> * curr = xnode->first_node(); curr; curr = curr->next_sibling()){
		if (string(curr->name()) == "name"){
			name = curr->value();
		}else if (string(curr->name()) == "status"){
			status = curr->value();
		}else if (string(curr->name()) == "description"){
			description = curr->value();
		}else if (string(curr->name()) == "attack"){
			attack = new CreatureAttack(curr);
		}else if (string(curr->name()) == "vulnerability"){
			vulnerability.push_back(curr->value());
		}else if (string(curr->name()) == "trigger"){
			Trigger * trigger = new Trigger(curr);
			trigger_list.push_back(trigger);
		}


	}
}


