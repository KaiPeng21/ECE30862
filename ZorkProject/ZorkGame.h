/*
 * ZorkGame.h
 *
 *  Created on: Nov 24, 2016
 *      Author: peng81
 */

#ifndef ZORKGAME_H_
#define ZORKGAME_H_

#define ERR -1

#include "rapidxml-1.13/rapidxml.hpp"
#include "rapidxml-1.13/rapidxml_utils.hpp"
#include "rapidxml-1.13/rapidxml_print.hpp"

#include "Room.h"
#include "Container.h"
#include "Item.h"
#include "Creature.h"
#include "Trigger.h"

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <cstdlib>
#include <fstream>
#include <iterator>
#include <sstream>
#include <stdio.h>
#include <string.h>

using namespace std;
using namespace rapidxml;


class ZorkGame {
public:
	xml_node<> *mapnode;

	string userInput;
	bool game_is_over;
	bool is_overriden;
	Room *curr_room;
	vector<string> inventory;


	ZorkGame(xml_node<> **mapn);
	virtual ~ZorkGame();

	void startGame();
	void checkUserInput();
	void checkInput(string input);
	void change_room(string direction);
	void show_inventory();
	void take(string takeItem);
	void open(string openContainer);
	void read(string readItem);
	void drop(string dropItem);
	void put(string putItem, string inContainer);
	void turnon(string turnonItem);
	void attack(string atkCreature, string withItem);
	void show_room_condition();

	void Add(string obj, string place);
	void Delete(string obj);
	void Update(string obj, string newStatus);
	void GameOver();

	string ztype(string obj);
	bool trigger_check();
	bool trigger_condition_met(Trigger* trigger);
	bool trig_owner_met(Trigger* trigger);
	bool trig_status_met(Trigger* trigger);
	void implement_trigger(Trigger* trigger);
	bool owner_has_object(string owner, string obj);
	bool object_meet_status(string obj, string status);

	vector<Room*> vec_room;
	vector<Container*> vec_container;
	vector<Item*> vec_item;
	vector<Creature*> vec_creature;

private:
	void xml_setup();
	void remove_from_vec(vector<string> &vec, int ind);
	void remove_from_vec(vector<string> &vec, string str);
	void remove_from_vec(vector<Border *> &vec, string str);
	// debugging functions


};

#endif /* ZORKGAME_H_ */
