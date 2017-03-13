/*
 * AttackCondition.h
 *
 *  Created on: Nov 26, 2016
 *      Author: peng81
 */

#ifndef ATTACKCONDITION_H_
#define ATTACKCONDITION_H_

#include "rapidxml-1.13/rapidxml.hpp"
#include "rapidxml-1.13/rapidxml_utils.hpp"
#include "rapidxml-1.13/rapidxml_print.hpp"
using namespace std;
using namespace rapidxml;

class AttackCondition {
public:
	string object;
	string status;

	AttackCondition(xml_node<>* xnode);
	virtual ~AttackCondition();

private:
	void initiailze(xml_node<>* xnode);
};

#endif /* ATTACKCONDITION_H_ */
