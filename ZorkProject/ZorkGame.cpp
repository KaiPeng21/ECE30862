/*
 * ZorkGame.cpp
 *
 *  Created on: Nov 24, 2016
 *      Author: peng81
 */

#include "ZorkGame.h"


ZorkGame::ZorkGame(xml_node<> **mapn){
	// TODO Auto-generated constbructor stub
	mapnode = *mapn;
	game_is_over = false;
	is_overriden = false;

	try{
		xml_setup();
	}catch(int err){
		cout << "Error settting up xml files";
		game_is_over = true;
	}

	curr_room = vec_room.front();
}

ZorkGame::~ZorkGame() {
	// TODO Auto-generated destructor stub
}

void ZorkGame::startGame(){

	show_room_condition();

	while(!game_is_over){

		is_overriden = trigger_check();
		if (is_overriden){
			continue;
		}

		getline(cin, userInput);
		if (string(userInput) == "q"){
			break;
		}

		is_overriden = trigger_check();
		if (is_overriden){
			continue;
		}

		// check userInput
		checkUserInput();
		userInput = "";


	}

	cout << "end Game";
	return;
}

/*********************CHECK USER INPUT FUNCTIONS************************/

void ZorkGame::checkInput(string input){

	if (input == "n" || input == "s" || input == "e" || input == "w"){
		change_room(input);
	}
	else if (input == "i"){
		show_inventory();
	}
	else if (input.find("take ") != string::npos){
		string command = input.substr(5);
		take(command);
	}
	else if (input.find("open ") != string::npos){
		string command = input.substr(5);
		open(command);
	}
	else if (input.find("read ") != string::npos){
		string command = input.substr(5);
		read(command);
	}
	else if (input.find("drop ") != string::npos){
		string command = input.substr(5);
		drop(command);
	}else if (input.find("put ") != string::npos && input.find("in ") != string::npos){
		int found = input.find("in ");
		string command = input.substr(4, found-5);
		string command2 = input.substr(found+3);

		//cout << "command: " << command << endl;
		//cout << "command2: " << command2 << endl;

		put(command, command2);
	}else if (input.find("turn on ") != string::npos){
		string command = input.substr(8);

		//cout << "command: " << command << endl;

		turnon(command);
	}else if (input.find("attack ") != string::npos && input.find("with ") != string::npos){
		int found = input.find("with ");
		string command = input.substr(7,found-8);
		string command2 = input.substr(found+5);

		//cout << "attack command: " << command << ",,," << command2 << endl;

		attack(command, command2);
	}else if (input == "curr room" || input == "show room condition"){
		show_room_condition();
	}else{
		if (input == userInput){
			cout << "Please Enter a Valid Command" << endl;
		}
	}

	// behind the scene commands
	if (input != userInput){
		if (input.find("Add ") != string::npos && input.find("to ") != string::npos){
			int found = input.find("to ");
			string command = input.substr(4, found-5);
			string command2 = input.substr(found+3);

			Add(command, command2);
		}else if (input.find("Delete ") != string::npos){
			string command = input.substr(7);

			//cout << "Delete command: " << command << endl;

			Delete(command);
		}else if (input.find("Update ") != string::npos && input.find("to ") != string::npos){
			int found = input.find("to ");
			//cout << "found = " << found << endl;
			string command = input.substr(7, found-8);
			string command2 = input.substr(found+3);

			//cout << "Update command 1,2 " << command << ",,," << command2 << endl;

			Update(command, command2);
		}else if (input == "Game Over"){
			GameOver();
		}
	}
}

void ZorkGame::checkUserInput(){
	checkInput(userInput);
}

void ZorkGame::change_room(string direction){
	Room * new_room = curr_room;
	string matching;

	if (direction == "n"){
		matching = "north";
	}else if (direction == "s"){
		matching = "south";
	}else if (direction == "w"){
		matching = "west";
	}else if (direction == "e"){
		matching = "east";
	}else{
		cout << "invalid direction" << endl;
		throw 1;
	}

	for (unsigned int i = 0; i < curr_room->border_list.size(); i++){
		if (curr_room->border_list[i]->direction == matching){
			for (unsigned int j = 0; j < vec_room.size(); j++){
				if (vec_room[j]->name == curr_room->border_list[i]->name){
					new_room = vec_room[j];
					break;
				}
			}
			break;
		}
	}
	if (new_room == curr_room){
		cout << "can't go that way!" << endl;
	}else{
		curr_room = new_room;
		cout << "move to room " + curr_room->name << endl;
	}

	show_room_condition();
}

void ZorkGame::show_inventory(){
	if (inventory.size() == 0){
		cout << "Inventory: empty" << endl;
	}else{
		cout << "Inventory: ";
		for (unsigned int i = 0; i < inventory.size()-1; i++){
			cout << inventory[i] + ", ";
		}
		cout << inventory[inventory.size()-1];
		cout << endl;
	}
}

void ZorkGame::take(string takeItem){
	for (unsigned int i = 0; i < curr_room->item_list.size(); i++){
		if (curr_room->item_list[i] == takeItem){
			inventory.push_back(takeItem);
			remove_from_vec(curr_room->item_list, i);
			cout << takeItem << " has been added to inventory" << endl;
			return;
		}
	}

	for (unsigned int i = 0; i < curr_room->container_list.size(); i++){
		for (unsigned int j = 0; j < vec_container.size(); j++){
			if (vec_container[j]->status == "unlocked"
					&& vec_container[j]->name == curr_room->container_list[i]){
				for (unsigned int k = 0; k < vec_container[j]->item_list.size(); k++){
					if (vec_container[j]->item_list[k] == takeItem){
						inventory.push_back(takeItem);
						remove_from_vec(vec_container[j]->item_list, k);
						cout << takeItem << " has been added to inventory" << endl;
						return;
					}
				}
			}
		}
	}

	cout << "There is no such item to take! " << endl;
}

void ZorkGame::open(string openContainer){
	if (openContainer == "exit" && curr_room->type == "exit"){
		GameOver();
		return;
	}

	for (unsigned int i = 0; i < curr_room->container_list.size(); i++){
		if (curr_room->container_list[i] == openContainer){
			for (unsigned int j = 0; j < vec_container.size(); j++){
				if (vec_container[j]->name == openContainer){
					if (vec_container[j]->accept_list.size() != 0 && vec_container[j]->status == "locked"){
						cout << openContainer << " is locked" << endl;
						cout << "You need ";
						for (unsigned int k = 0; k < vec_container[j]->accept_list.size()-1; k++){
							cout << vec_container[j]->accept_list[k] << ", ";
						}
						cout << vec_container[j]->accept_list.back();
						cout << " to open it" << endl;
						return;
					}

					vec_container[j]->status = "unlocked";

					if (vec_container[j]->item_list.size() == 0){
						cout << openContainer << " is empty" << endl;
						return;
					}
					cout << openContainer << " contains ";
					for (unsigned int k = 0; k < vec_container[j]->item_list.size()-1; k++){
						cout << vec_container[j]->item_list[k] << ", ";
					}
					cout << vec_container[j]->item_list.back() << endl;
					return;
				}
			}
		}
	}

	cout << "There is no such container in the room! " << endl;
}

void ZorkGame::read(string readItem){
	for (unsigned int i = 0; i < inventory.size(); i++){
		if (readItem == inventory[i]){
			for (unsigned int j = 0; j < vec_item.size(); j++){
				if (vec_item[j]->name == readItem){
					cout << vec_item[j]->writing << endl;
					return;
				}
			}
		}
	}

	cout << "There is no such item to read" << endl;
	return;
}

void ZorkGame::drop(string dropItem){
	for (unsigned int i = 0; i < inventory.size(); i++){
		if (inventory[i] == dropItem){
			remove_from_vec(inventory, dropItem);
			curr_room->item_list.push_back(dropItem);
			cout << dropItem << " has been dropped" << endl;
			return;
		}
	}

	cout << "There is no such item to drop" << endl;
	return;
}

void ZorkGame::put(string putItem, string inContainer){
	for (unsigned int i = 0; i < inventory.size(); i++){
		if (putItem == inventory[i]){
			for (unsigned int j = 0; j < curr_room->container_list.size(); j++){
				if (inContainer == curr_room->container_list[j]){
					for (unsigned int k = 0; k < vec_container.size(); k++){
						if (vec_container[k]->name == inContainer){
							if (!vec_container[k]->is_accepted_by_container(putItem)){
								cout << putItem << " cannot be put into " << inContainer << endl;
								return;
							}
							/*
							else if (vec_container[k]->status == "locked"){
								cout << "Please open " << inContainer << " first" << endl;
								return;
							}*/
							vec_container[k]->item_list.push_back(putItem);
							remove_from_vec(inventory, putItem);
							cout << putItem << " has been put in " << inContainer << endl;
							vec_container[k]->status = "unlocked";
							return;
						}
					}
				}
			}
			cout << "There is no such container to put items in." << endl;
			return;
		}
	}

	cout << "There is no such item to put" << endl;
	return;
}

void ZorkGame::turnon(string turnonItem){

	for (unsigned int i = 0; i < inventory.size(); i++){
		if (turnonItem == inventory[i]){
			for (unsigned int j = 0; j < vec_item.size(); j++){
				if (vec_item[j]->name == turnonItem){
					if (vec_item[i]->turnon == 0){
						cout << turnonItem << " cannot be turned on" << endl;
						return;
					}
					cout << "You activated the " << turnonItem << endl;
					cout << vec_item[j]->turnon->print << endl;
					checkInput(vec_item[i]->turnon->action);
					return;
				}
			}
		}
	}

	cout << "There is no such item can be turned on" << endl;
}


void ZorkGame::attack(string atkCreature, string withItem){
	for (unsigned int i = 0; i < curr_room->creature_list.size(); i++){
		if (curr_room->creature_list[i] == atkCreature){
			for (unsigned int j = 0; j < inventory.size(); j++){
				if (inventory[j] == withItem){
					for (unsigned int k = 0; k < vec_creature.size(); k++){
						if (vec_creature[k]->name == atkCreature){
							for (unsigned int l = 0; l < vec_creature[k]->vulnerability.size(); l++){
								if (vec_creature[k]->vulnerability[l] == withItem){
									cout << "You assault the " << atkCreature << " with " << withItem << endl;
									if (vec_creature[k]->attack){
										cout << vec_creature[k]->attack->print << endl;
										for (unsigned int m = 0; m < vec_creature[k]->attack->action.size(); m++){
											checkInput(vec_creature[k]->attack->action[m]);
										}
									}



									return;
								}
							}
							cout << "You can't assault " << atkCreature << " with this item" << endl;
							return;
						}
					}
				}
			}
			cout << "You don't have such item" << endl;
			return;
		}
	}

	cout << "There is no such creature" << endl;
}

void ZorkGame::show_room_condition(){
	cout << "----------" << endl;
	cout << curr_room->description << endl;
	if (curr_room->item_list.size() != 0){
		cout << "Items in this room: ";
		for (unsigned int i = 0; i < curr_room->item_list.size()-1; i++){
			cout << curr_room->item_list[i] << ", ";
		}
		cout << curr_room->item_list.back();
		cout << endl;
	}
	if (curr_room->container_list.size() != 0){
		cout << "Containers in this room: ";
		for (unsigned int i = 0; i < curr_room->container_list.size()-1; i++){
			cout << curr_room->container_list[i] << ", ";
		}
		cout << curr_room->container_list.back();
		cout << endl;
	}
	if (curr_room->creature_list.size() != 0){
		cout << "Creatures in this room: ";
		for (unsigned int i = 0; i < curr_room->creature_list.size()-1; i++){
			cout << curr_room->creature_list[i] << ", ";
		}
		cout << curr_room->creature_list.back();
		cout << endl;
	}
	if (curr_room->border_list.size() != 0){
		cout << "You may go ";
		for (unsigned int i = 0; i < curr_room->border_list.size()-1; i++){
			cout << curr_room->border_list[i]->direction << ", ";
		}
		cout << curr_room->border_list.back()->direction;
		cout << endl << "----------" << endl;
	}
}
/********************************************************************/


void ZorkGame::Add(string obj, string place){
	string objtype;

	for (unsigned int i = 0; i < vec_item.size(); i++){
		if (vec_item[i]->name == obj){
			objtype = "item";
			break;
		}
	}
	for (unsigned int i = 0; i < vec_creature.size(); i++){
		if (vec_creature[i]->name == obj){
			objtype = "creature";
			break;
		}
	}
	for (unsigned int i = 0; i < vec_container.size(); i++){
		if (vec_container[i]->name == obj){
			objtype = "container";
			break;
		}
	}


	for (unsigned int i = 0; i < vec_room.size(); i++){
		if (vec_room[i]->name == place){
			if (objtype == "item"){
				vec_room[i]->item_list.push_back(obj);
			}else if (objtype == "creature"){
				vec_room[i]->creature_list.push_back(obj);
			}else if (objtype == "container"){
				vec_room[i]->container_list.push_back(obj);
			}
			cout << obj << " appeared in the room " << vec_room[i]->name << endl;
			return;
		}
	}
	for (unsigned int i = 0; i < vec_container.size(); i++){
		if (vec_container[i]->name == place){
			if (objtype == "item"){
				vec_container[i]->item_list.push_back(obj);
			}
			cout << obj << " appeared in the container " << vec_container[i]->name << endl;
		    return;
		}
	}
}
void ZorkGame::Delete(string obj){

	remove_from_vec(inventory, obj);
	for (unsigned int i = 0; i < vec_room.size(); i++){
		remove_from_vec(vec_room[i]->item_list, obj);
		remove_from_vec(vec_room[i]->creature_list, obj);
		remove_from_vec(vec_room[i]->container_list, obj);
	}
	for (unsigned int i = 0; i < vec_room.size(); i++){
		remove_from_vec(vec_room[i]->border_list, obj);
	}

}
void ZorkGame::Update(string obj, string newStatus){

	for (unsigned int i = 0; i < vec_item.size(); i++){
		if (vec_item[i]->name == obj){
			vec_item[i]->status = newStatus;

			//cout << "updating " << vec_item[i]->name << " to " << newStatus << endl;

			return;
		}
	}
	for (unsigned int i = 0; i < vec_creature.size(); i++){
		if (vec_creature[i]->name == obj){
			vec_creature[i]->status = newStatus;
			return;
		}
	}
	for (unsigned int i = 0; i < vec_container.size(); i++){
		if (vec_container[i]->name == obj){
			vec_container[i]->status = newStatus;
			return;
		}
	}
	for (unsigned int i = 0; i < vec_room.size(); i++){
		if (vec_room[i]->name == obj){
			vec_room[i]->status = newStatus;
			return;
		}
	}
}
void ZorkGame::GameOver(){
	game_is_over = true;
	cout << "Victory!" << endl;
}

string ZorkGame::ztype(string obj){

	if (obj == "inventory"){
		//cout << "ztype: inventory" << endl;
		return "inventory";
	}

	for (unsigned int i = 0; i < vec_item.size(); i++){
		if (vec_item[i]->name == obj){
			return "item";
		}
	}
	for (unsigned int i = 0; i < vec_creature.size(); i++){
		if (vec_creature[i]->name == obj){
			return "creature";
		}
	}
	for (unsigned int i = 0; i < vec_container.size(); i++){
		if (vec_container[i]->name == obj){
			return "container";
		}
	}
	for (unsigned int i = 0; i < vec_room.size(); i++){
		if (vec_room[i]->name == obj){
			return "room";
		}
	}
	return "";
}

bool ZorkGame::trigger_check(){

	for (unsigned int i = 0; i < vec_item.size(); i++){
		for (unsigned int j = 0; j < vec_item[i]->trigger_list.size(); j++){
			if (trigger_condition_met(vec_item[i]->trigger_list[j])){
				return true;
			}
		}
	}
	for (unsigned int i = 0; i < vec_room.size(); i++){
		for (unsigned int j = 0; j < vec_room[i]->trigger_list.size(); j++){
			if (trigger_condition_met(vec_room[i]->trigger_list[j])){
				return true;
			}
		}
	}
	for (unsigned int i = 0; i < vec_container.size(); i++){
		for (unsigned int j = 0; j < vec_container[i]->trigger_list.size(); j++){
			if (trigger_condition_met(vec_container[i]->trigger_list[j])){
				return true;
			}
		}
	}
	for (unsigned int i = 0; i < vec_creature.size(); i++){
		for (unsigned int j = 0; j < vec_creature[i]->trigger_list.size(); j++){
			if (trigger_condition_met(vec_creature[i]->trigger_list[j])){
				return true;
			}
		}
	}

	return false;
}

bool ZorkGame::trigger_condition_met(Trigger* trigger){
	bool is_triggered = false;

	if (trigger->command == ""){

		if (trigger->owner && trigger->status){
			if (trig_owner_met(trigger) && trig_status_met(trigger)){
				is_triggered = true;
			}
		}
		else if (trigger->status){
			if (trig_status_met(trigger)){
				is_triggered = true;
			}
		}
		else if (trigger->owner){
			if (trig_owner_met(trigger)){
				is_triggered = true;
			}
		}

	}else{
		if (trigger->command != userInput){
			return false;
		}

		if (trigger->owner && trigger->status){
			if (trig_owner_met(trigger) && trig_status_met(trigger)){
				is_triggered = true;
			}
		}
		else if (trigger->status){
			if (trig_status_met(trigger)){
				is_triggered = true;
			}
		}
		else if (trigger->owner){
			if (trig_owner_met(trigger)){
				is_triggered = true;
			}
		}
	}

	if (is_triggered){
		implement_trigger(trigger);
		return true;
	}

	return false;
}

void ZorkGame::implement_trigger(Trigger* trigger){

	cout << trigger->print << endl;
	for (unsigned int j = 0; j < trigger->action.size(); j++){
		//cout << "debug" << trigger->action[j] << endl;
		checkInput(trigger->action[j]);
	}

	//cout << "implementing trigger " << obj << " meet " << status << endl;

	if (trigger->type == "single"){
		trigger->type = "used";
	}
}

bool ZorkGame::trig_owner_met(Trigger* trigger){
	if (trigger->owner){
		string owner = trigger->owner->owner;
		string obj = trigger->owner->object;
		if ((trigger->owner->has == "yes" && owner_has_object(owner, obj))
				|| (trigger->owner->has == "no" && !owner_has_object(owner, obj))){
			if (trigger->type != "used"){
				return true;
			}
		}
	}

	return false;
}
bool ZorkGame::trig_status_met(Trigger* trigger){
	 if (trigger->status){
		string status = trigger->status->status;
		string obj = trigger->status->object;
		if (object_meet_status(obj, status)){
			if (trigger->type != "used"){
				return true;
			}
		}
	}

	return false;
}

bool ZorkGame::owner_has_object(string owner, string obj){
	string owner_type = ztype(owner);
	string obj_type = ztype(obj);

	if (owner_type == "inventory"){
		if (obj_type == "item"){
			for (unsigned int i = 0; i < inventory.size(); i++){
				if (inventory[i] == obj){
					return true;
				}
			}
		}
	}else if (owner_type == "room"){
		if (obj_type == "item"){
			for (unsigned int i = 0; i < vec_room.size(); i++){
				if (vec_room[i]->name == owner){
					return vec_room[i]->has_item(obj);
				}
			}
		}else if (obj_type == "container"){
			for (unsigned int i = 0; i < vec_room.size(); i++){
				if (vec_room[i]->name == owner){
					return vec_room[i]->has_container(obj);
				}
			}
		}else if (obj_type == "creature"){
			for (unsigned int i = 0; i < vec_room.size(); i++){
				if (vec_room[i]->name == owner){
					return vec_room[i]->has_creature(obj);
				}
			}
		}
	}else if (owner_type == "container"){
		if (obj_type == "item"){
			for (unsigned int i = 0; i < vec_container.size(); i++){
				if (vec_container[i]->name == owner){
					return vec_container[i]->has_item(obj);
				}
			}
		}
	}

	return false;
}

bool ZorkGame::object_meet_status(string obj, string status){
	string obj_type = ztype(obj);

	if (obj_type == "item"){
		for (unsigned int i = 0; i < vec_item.size(); i++){
			if (vec_item[i]->name == obj){
				if (vec_item[i]->status == status){
					return true;
				}
			}
		}
	}
	else if (obj_type == "room"){
		for (unsigned int i = 0; i < vec_room.size(); i++){
			if (vec_room[i]->name == obj){
				if (vec_room[i]->status == status){
					return true;
				}
			}
		}
	}
	else if (obj_type == "container"){
		for (unsigned int i = 0; i < vec_container.size(); i++){
			if (vec_container[i]->name == obj){
				if (vec_container[i]->status == status){
					return true;
				}
			}
		}
	}
	else if (obj_type == "creature"){
		for (unsigned int i = 0; i < vec_creature.size(); i++){
			if (vec_creature[i]->name == obj){
				if (vec_creature[i]->status == status){
					return true;
				}
			}
		}
	}

	return false;
}

void ZorkGame::xml_setup(){


	//xml_document<> doc;


	// sort xml node to respective types

	vector<xml_node<>*> room_xlist;
	vector<xml_node<>*> container_xlist;
	vector<xml_node<>*> item_xlist;
	vector<xml_node<>*> creature_xlist;

	for(xml_node<>* node = mapnode->first_node(); node; node = node->next_sibling()){
		if (string(node->name()) == "room"){
			room_xlist.push_back(node);
			//cout << "add a room" << endl;
		}else if (string(node->name()) == "container"){
			container_xlist.push_back(node);
			//cout << "add a container" << endl;
		}else if (string(node->name()) == "item"){
			item_xlist.push_back(node);
			//cout << "add a item" << endl;
		}else if (string(node->name()) == "creature"){
			creature_xlist.push_back(node);
			//cout << "add a creature" << endl;
		}


	}

	// add zcomponents to map

	for (unsigned int i = 0; i < room_xlist.size(); i++){
		Room * room = new Room(room_xlist[i]);
		vec_room.push_back(room);
	}
	for (unsigned int i = 0; i < container_xlist.size(); i++){
		Container * container = new Container(container_xlist[i]);
		vec_container.push_back(container);
	}
	for (unsigned int i = 0; i < item_xlist.size(); i++){
		Item * item = new Item(item_xlist[i]);
		vec_item.push_back(item);
	}
	for (unsigned int i = 0; i < creature_xlist.size(); i++){
		Creature * creature = new Creature(creature_xlist[i]);
		vec_creature.push_back(creature);
	}

	return;
}

/*
		cout << "room_xlist size: " << room_xlist.size() << endl;
		cout << "container_xlist size: " << container_xlist.size() << endl;
		cout << "item_xlist size: " << item_xlist.size() << endl;
		cout << "creature_xlist size: " << creature_xlist.size() << endl;
		cout << "=====end of loop====" << endl;

		cout << "room size: " << vec_room.size() << endl;
		cout << "container size: " << vec_container.size() << endl;
		cout << "item size: " << vec_item.size() << endl;
		cout << "creature size: " << vec_creature.size() << endl;
 *
 */

void ZorkGame::remove_from_vec(vector<string> &vec, int ind){
	vec.erase(vec.begin()+ind);
}

void ZorkGame::remove_from_vec(vector<string> &vec, string str){
	for (unsigned int i = 0; i < vec.size(); i++){
		if (vec[i] == str){
			remove_from_vec(vec, i);
		}
	}
}

void ZorkGame::remove_from_vec(vector<Border *> &vec, string str){
	for (unsigned int i = 0; i < vec.size(); i++){
		if (vec[i]->name == str){
			vec.erase(vec.begin()+i);
		}
	}
}


