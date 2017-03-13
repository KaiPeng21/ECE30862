/*
 * Container.cpp
 *
 *  Created on: Nov 20, 2016
 *      Author: peng81
 */

#include "Container.h"

Container::Container(xml_node<>* xnode) {
	// TODO Auto-generated constructor stub
	initialize(xnode);
}

Container::~Container() {
	// TODO Auto-generated destructor stub
}

void Container::initialize(xml_node<>* xnode){
	status = "locked";

	for (xml_node<> * curr = xnode->first_node(); curr; curr = curr->next_sibling()){
		if (string(curr->name()) == "name"){
			name = curr->value();
		}else if (string(curr->name()) == "status"){
			status = curr->value();
		}else if (string(curr->name()) == "description"){
			description = curr->value();
		}else if (string(curr->name()) == "accept"){
			accept_list.push_back(curr->value());
		}else if (string(curr->name()) == "item"){
			item_list.push_back(curr->value());
		}else if (string(curr->name()) == "trigger"){
			Trigger * trigger = new Trigger(curr);
			trigger_list.push_back(trigger);
		}

	}

}

bool Container::is_accepted_by_container(string obj){
	if (accept_list.size() == 0){
		return true;
	}

	for (unsigned int i = 0; i < accept_list.size(); i++){
		if (accept_list[i] == obj){
			return true;
		}
	}

	return false;
}

bool Container::has_item(string obj){
	for (unsigned int i = 0; i < item_list.size(); i++){
		if (item_list[i] == obj){
			return true;
		}
	}
	return false;
}
