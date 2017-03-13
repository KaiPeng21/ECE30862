/*
 * TrigOwner.cpp
 *
 *  Created on: Nov 26, 2016
 *      Author: peng81
 */

#include "TrigOwner.h"

TrigOwner::TrigOwner(xml_node<>* xnode) {
	// TODO Auto-generated constructor stub
	initialize(xnode);

}

TrigOwner::~TrigOwner() {
	// TODO Auto-generated destructor stub
}

void TrigOwner::initialize(xml_node<>* xnode){
	for (xml_node<> * curr = xnode->first_node(); curr; curr = curr->next_sibling()){
		if (string(curr->name()) == "object"){
			object = curr->value();
		}else if (string(curr->name()) == "has"){
			has = curr->value();
		}else if (string(curr->name()) == "owner"){
			owner = curr->value();
		}
	}
}
