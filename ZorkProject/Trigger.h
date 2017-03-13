/*
 * Trigger.h
 *
 *  Created on: Nov 20, 2016
 *      Author: peng81
 */

#ifndef TRIGGER_H_
#define TRIGGER_H_

#include "ZComponent.h"
#include "TrigStatus.h"
#include "TrigOwner.h"


#include "rapidxml-1.13/rapidxml.hpp"
#include "rapidxml-1.13/rapidxml_utils.hpp"
#include "rapidxml-1.13/rapidxml_print.hpp"

using namespace std;
using namespace rapidxml;

class Trigger {
public:
	string type;
	string command;
	string print;
	vector<string> action;
	TrigOwner *owner;
	TrigStatus *status;

	Trigger(xml_node<> * xnode);
	virtual ~Trigger();

	int num_child(xml_node<> * xnode);


private:
	void initialize(xml_node<>* xnode);
};

#endif /* TRIGGER_H_ */
