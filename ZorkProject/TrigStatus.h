/*
 * TrigStatus.h
 *
 *  Created on: Nov 26, 2016
 *      Author: peng81
 */

#ifndef TRIGSTATUS_H_
#define TRIGSTATUS_H_

#include <string>

#include "rapidxml-1.13/rapidxml.hpp"
#include "rapidxml-1.13/rapidxml_utils.hpp"
#include "rapidxml-1.13/rapidxml_print.hpp"

using namespace std;
using namespace rapidxml;

class TrigStatus {
public:
	string object;
	string status;

	TrigStatus(xml_node<>* xnode);
	virtual ~TrigStatus();

private:
	void initialize(xml_node<>* xnode);
};

#endif /* TRIGSTATUS_H_ */
