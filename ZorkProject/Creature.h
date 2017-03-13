/*
 * Creature.h
 *
 *  Created on: Nov 20, 2016
 *      Author: peng81
 */

#ifndef CREATURE_H_
#define CREATURE_H_

#include <string>
#include <vector>

#include "ZComponent.h"
#include "Trigger.h"
#include "CreatureAttack.h"

#include "rapidxml-1.13/rapidxml.hpp"
#include "rapidxml-1.13/rapidxml_utils.hpp"
#include "rapidxml-1.13/rapidxml_print.hpp"
using namespace std;
using namespace rapidxml;

class Creature: public ZComponent {
public:
	string name;
	string status;
	string description;
	vector<string> vulnerability;
	CreatureAttack *attack;
	vector<Trigger *> trigger_list;

	Creature(xml_node<>* xnode);
	virtual ~Creature();

private:
	void initialize(xml_node<>* xnode);
};

#endif /* CREATURE_H_ */
