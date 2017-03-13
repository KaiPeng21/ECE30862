/*
 * CreatureAttack.h
 *
 *  Created on: Nov 26, 2016
 *      Author: peng81
 */

#ifndef CREATUREATTACK_H_
#define CREATUREATTACK_H_

#include "rapidxml-1.13/rapidxml.hpp"
#include "rapidxml-1.13/rapidxml_utils.hpp"
#include "rapidxml-1.13/rapidxml_print.hpp"
#include <string>
#include <vector>
#include "AttackCondition.h"

using namespace std;
using namespace rapidxml;

class CreatureAttack {
public:
	AttackCondition * condition;
	string print;
	vector<string> action;

	CreatureAttack(xml_node<>* xnode);
	virtual ~CreatureAttack();

private:
	void initialize(xml_node<>* xnode);
};

#endif /* CREATUREATTACK_H_ */
