/*
 * Trigger.cpp
 *
 *  Created on: Nov 20, 2016
 *      Author: peng81
 */

#include "Trigger.h"

Trigger::Trigger(xml_node<>* xnode) {
	// TODO Auto-generated constructor stub
	initialize(xnode);
}

Trigger::~Trigger() {
	// TODO Auto-generated destructor stub
}

void Trigger::initialize(xml_node<>* xnode){
	type = "single";
	command = "";
	print = "";

	for (xml_node<> * curr = xnode->first_node(); curr; curr = curr->next_sibling()){
		if (string(curr->name()) == "type"){
			type = curr->value();
		}else if (string(curr->name()) == "print"){
			print = curr->value();
		}else if (string(curr->name()) == "command"){
			command = curr->value();
		}else if (string(curr->name()) == "action"){
			action.push_back(curr->value());
		}else if (string(curr->name()) == "condition"){
			if (num_child(curr) == 2){
				status = new TrigStatus(curr);
			}else if (num_child(curr) == 3){
				owner = new TrigOwner(curr);
			}
		}

	}
}

int Trigger::num_child(xml_node<> * xnode){
	int ct = 0;
	for (xml_node<> * curr = xnode->first_node(); curr; curr = curr->next_sibling()){
		ct++;
	}
	return ct;
}

/*
string type;
string command;
string print;
vector<string> action;
TrigOwner owner;
TrigStatus status;
*/
