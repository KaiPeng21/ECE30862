/*
 * TrigStatus.cpp
 *
 *  Created on: Nov 26, 2016
 *      Author: peng81
 */

#include "TrigStatus.h"

TrigStatus::TrigStatus(xml_node<>* xnode) {
	// TODO Auto-generated constructor stub
	initialize(xnode);

}

TrigStatus::~TrigStatus() {
	// TODO Auto-generated destructor stub
}

void TrigStatus::initialize(xml_node<>* xnode){
	for (xml_node<> * curr = xnode->first_node(); curr; curr = curr->next_sibling()){
		if (string(curr->name()) == "object"){
			object = curr->value();
		}else if (string(curr->name()) == "status"){
			status = curr->value();
		}
	}
}
