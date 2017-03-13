/*
 * Container.h
 *
 *  Created on: Nov 20, 2016
 *      Author: peng81
 */

#ifndef CONTAINER_H_
#define CONTAINER_H_

#include <string>
#include <vector>

#include "ZComponent.h"
#include "Trigger.h"
#include "Item.h"

#include "rapidxml-1.13/rapidxml.hpp"
#include "rapidxml-1.13/rapidxml_utils.hpp"
#include "rapidxml-1.13/rapidxml_print.hpp"
using namespace std;
using namespace rapidxml;

class Container: public ZComponent{
public:
	string name;
	string status;
	string description;
	vector<string> accept_list;
	vector<string> item_list;
	vector<Trigger *> trigger_list;

	Container(xml_node<>* xnode);
	virtual ~Container();

	bool is_accepted_by_container(string obj);
	bool has_item(string obj);

private:
	void initialize(xml_node<>* xnode);
};

#endif /* CONTAINER_H_ */
