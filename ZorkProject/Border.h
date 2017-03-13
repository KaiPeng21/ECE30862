/*
 * Border.h
 *
 *  Created on: Nov 26, 2016
 *      Author: peng81
 */

#ifndef BORDER_H_
#define BORDER_H_

#include <string>
#include <iostream>
#include "rapidxml-1.13/rapidxml.hpp"
#include "rapidxml-1.13/rapidxml_utils.hpp"
#include "rapidxml-1.13/rapidxml_print.hpp"
using namespace std;
using namespace rapidxml;

class Border {
public:
	string name;
	string direction;

	Border(xml_node<>* xnode);
	virtual ~Border();

private:
	void initialize(xml_node<>* xnode);
};

#endif /* BORDER_H_ */
