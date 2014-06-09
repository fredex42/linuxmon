/*
 * base.cpp
 *
 *  Created on: 9 Jun 2014
 *      Author: andy
 */

#include <iostream>
#include "base.h"
using namespace std;

base::base() {
	// TODO Auto-generated constructor stub
	refcount=0;
	warn=cout;
	debug=cout;
}

base::~base() {
	// TODO Auto-generated destructor stub
}

void base::ref()
{
	++refcount;
}

void base::unref()
{
	--refcount;
	if(refcount<1) delete this;
}
