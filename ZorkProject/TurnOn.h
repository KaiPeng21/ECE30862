/*
 * TurnOn.h
 *
 *  Created on: Nov 26, 2016
 *      Author: peng81
 */

#ifndef TURNON_H_
#define TURNON_H_

#include <string>
#include <iostream>

#include "rapidxml-1.13/rapidxml.hpp"
#include "rapidxml-1.13/rapidxml_utils.hpp"
#include "rapidxml-1.13/rapidxml_print.hpp"

using namespace std;
using namespace rapidxml;

class TurnOn {
public:
	string print;
	string action;
	TurnOn(xml_node<>* xnode);
	virtual ~TurnOn();

private:
	void initialize(xml_node<>* xnode);
};

#endif /* TURNON_H_ */
