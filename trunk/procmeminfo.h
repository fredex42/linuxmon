/*
 * procmeminfo.h
 *
 *  Created on: 18 Jun 2014
 *      Author: andy
 */

#ifndef PROCMEMINFO_H_
#define PROCMEMINFO_H_

#include <string>
#include <map>
#include <cstdlib>
#include <math.h>

using namespace std;

#include "procfile.h"

class sizeEntry: public base {
public:
	sizeEntry() {
		power=-1;
		size=-1;
		unitName="";
	}
	sizeEntry(string sizeParam,string unitName)
	{
		this->size=atoi(sizeParam.c_str());
		this->unitName=unitName;
		this->power=this->unitToPower(unitName);
	}
	sizeEntry(long size,string unitName)
	{
		this->size=size;
		this->unitName=unitName;
		this->power=this->unitToPower(unitName);
	}
	int getPower() const {
		return power;
	}

	void setPower(int power) {
		this->power = power;
	}

	long getSize() const {
		return size;
	}

	long realValue() {
		return size*pow(10,power);
	}

	void setSize(long size) {
		this->size = size;
	}

	const string& getUnitName() const {
		return unitName;
	}

	void setUnitName(const string& unitName) {
		this->unitName = unitName;
	}

private:
	int unitToPower(const string&);
	long size;
	string unitName;
	int power;
};

class procmeminfo: public procfile {
public:
	procmeminfo();
	virtual ~procmeminfo();
	int update();
	int db_commit(DB_REF reference);

	sizeEntry * get(string &name);

	void dump();
private:
	std::map<std::string,sizeEntry *>info;

};

#endif /* PROCMEMINFO_H_ */
