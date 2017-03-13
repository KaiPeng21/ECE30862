/*
 * Item.h
 *
 *  Created on: Nov 20, 2016
 *      Author: peng81
 */

#ifndef ITEM_H_
#define ITEM_H_

#include <string>
#include <vector>

#include "ZComponent.h"
#include "Trigger.h"
#include "TurnOn.h"

#include "rapidxml-1.13/rapidxml.hpp"
#include "rapidxml-1.13/rapidxml_utils.hpp"
#include "rapidxml-1.13/rapidxml_print.hpp"
using namespace std;
using namespace rapidxml;


class Item: public ZComponent{
public:
	string name;
	string status;
	string description;
	string writing;
	TurnOn *turnon;
	vector<Trigger *> trigger_list;

	Item(xml_node<>* xnode);
	virtual ~Item();

private:
	void initialize(xml_node<>* xnode);

};

#endif /* ITEM_H_ */
