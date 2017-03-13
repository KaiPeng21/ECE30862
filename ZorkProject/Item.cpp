/*
 * Item.cpp
 *
 *  Created on: Nov 20, 2016
 *      Author: peng81
 */

#include "Item.h"

Item::Item(xml_node<>* xnode) {
	// TODO Auto-generated constructor stub
	initialize(xnode);
}

Item::~Item() {
	// TODO Auto-generated destructor stub
}

void Item::initialize(xml_node<>* xnode){
	writing = "nothing written";

	for (xml_node<> * curr = xnode->first_node(); curr; curr = curr->next_sibling()){
		if (string(curr->name()) == "name"){
			name = curr->value();
		}else if (string(curr->name()) == "status"){
			status = curr->value();
		}else if (string(curr->name()) == "description"){
			description = curr->value();
		}else if (string(curr->name()) == "writing"){
			writing = curr->value();
		}else if (string(curr->name()) == "turnon"){
			turnon = new TurnOn(curr);
		}else if (string(curr->name()) == "trigger"){
			Trigger * trigger = new Trigger(curr);
			trigger_list.push_back(trigger);
		}

	}

	return;
}
