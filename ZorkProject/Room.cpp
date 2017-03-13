/*
 * Room.cpp
 *
 *  Created on: Nov 20, 2016
 *      Author: peng81
 */

#include "Room.h"

Room::Room(xml_node<>* xnode) {
	// TODO Auto-generated constructor stub
	initialize(xnode);
}

Room::~Room() {
	// TODO Auto-generated destructor stub
}

void Room::initialize(xml_node<> * xnode){

	type = "regular";

	for (xml_node<> * curr = xnode->first_node(); curr; curr = curr->next_sibling()){
		if (string(curr->name()) == "name"){
			name = curr->value();
		}else if (string(curr->name()) == "status"){
			status = curr->value();
		}else if (string(curr->name()) == "type"){
			type = curr->value();
		}else if (string(curr->name()) == "description"){
			description = curr->value();
		}else if (string(curr->name()) == "border"){
			Border * border = new Border(curr);
			border_list.push_back(border);
		}else if (string(curr->name()) == "container"){
			container_list.push_back(curr->value());
		}else if (string(curr->name()) == "item"){
			item_list.push_back(curr->value());
		}else if (string(curr->name()) == "creature"){
			creature_list.push_back(curr->value());
		}else if (string(curr->name()) == "trigger"){
			Trigger * trigger = new Trigger(curr);
			trigger_list.push_back(trigger);
		}
	}

	return;
}

bool Room::has_item(string obj){
	for (unsigned int i = 0; i < item_list.size(); i++){
		if (item_list[i] == obj){
			return true;
		}
	}
	return false;
}
bool Room::has_creature(string obj){
	for (unsigned int i = 0; i < creature_list.size(); i++){
		if (creature_list[i] == obj){
			return true;
		}
	}

	return false;
}
bool Room::has_container(string obj){
	for (unsigned int i = 0; i < container_list.size(); i++){
		if (container_list[i] == obj){
			return true;
		}
	}

	return false;
}
