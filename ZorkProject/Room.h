/*
 * Room.h
 *
 *  Created on: Nov 20, 2016
 *      Author: peng81
 */

#ifndef ROOM_H_
#define ROOM_H_

#include <string>
#include <vector>

#include "ZComponent.h"
#include "Trigger.h"
#include "Item.h"
#include "Container.h"
#include "Border.h"

#include "rapidxml-1.13/rapidxml.hpp"
#include "rapidxml-1.13/rapidxml_utils.hpp"
#include "rapidxml-1.13/rapidxml_print.hpp"
using namespace std;
using namespace rapidxml;


class Room : public ZComponent{
public:
	string name;
	string status;
	string type;
	string description;
	vector<Border *> border_list;
	vector<string> container_list;
	vector<string> item_list;
	vector<string> creature_list;
	vector<Trigger *> trigger_list;

	Room(xml_node<> * xnode);
	virtual ~Room();

	bool has_item(string obj);
	bool has_creature(string obj);
	bool has_container(string obj);

private:
	void initialize(xml_node<>* xnode);
};

#endif /* ROOM_H_ */
