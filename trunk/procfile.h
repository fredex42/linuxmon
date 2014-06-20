/*
 * procfile.h
 *
 *  Created on: 9 Jun 2014
 *      Author: andy
 */

#ifndef PROCFILE_H_
#define PROCFILE_H_


#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "base.h"

class fileerror: public exception
{
	virtual const char * what() const throw()
		{
		return "Unable to open /proc/stat";
		}
};// fileerror;

class procfile: public base {
public:
	procfile();
	virtual ~procfile();

	int db_commit(DB_REF reference);
protected:
	std::string metrictype;
};

#endif /* PROCFILE_H_ */
