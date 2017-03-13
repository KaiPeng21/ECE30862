/*
 * TrigOwner.h
 *
 *  Created on: Nov 26, 2016
 *      Author: peng81
 */

#ifndef TRIGOWNER_H_
#define TRIGOWNER_H_

#include <string>

#include "rapidxml-1.13/rapidxml.hpp"
#include "rapidxml-1.13/rapidxml_utils.hpp"
#include "rapidxml-1.13/rapidxml_print.hpp"

using namespace std;
using namespace rapidxml;

class TrigOwner {
public:
	string object;
	string has;
	string owner;

	TrigOwner(xml_node<>* xnode);
	virtual ~TrigOwner();
private:
	void initialize(xml_node<>* xnode);
};

#endif /* TRIGOWNER_H_ */
