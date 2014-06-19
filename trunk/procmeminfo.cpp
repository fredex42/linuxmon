/*
 * procmeminfo.cpp
 *
 *  Created on: 18 Jun 2014
 *      Author: andy
 */

#include "procmeminfo.h"
using namespace std;

procmeminfo::procmeminfo() {
	// TODO Auto-generated constructor stub

}

procmeminfo::~procmeminfo() {
	// TODO Auto-generated destructor stub
}

std::string& sizeEntry::powerToUnit(int pow,string& unitType)
{
std::string *tmp=NULL;

switch(pow){
case 3:
	tmp=new string("K");
	break;
case 6:
	tmp=new string("M");
	break;
case 9:
	tmp=new string("G");
	break;
case 12:
	tmp=new string("T");
	break;
}

std::string *rtn=new string;
(*rtn)=(*tmp)+unitType;
delete tmp;
return *rtn;
}

int sizeEntry::unitToPower(const string& unitName)
{
switch(unitName[0]){
case 'k':
case 'K':
	return 3;
case 'M':
	return 6;
case 'G':
case 'g':
	return 9;
case 'T':
case 't':
	return 12;
case 'P':
	return 15;
case 'm':
	return -3;
case 'u':
	return -6;
case 'n':
	return -9;
case 'p':
	return -12;
default:
	return 0;
}
return 0;
}

void sizeEntry::normalise() {
int power=0;
float value=this->size;

while(value>1){
	power+=3;
	value=value/pow(10,3);
}
power-=3;
this->size=this->size/pow(10,power);
this->power=this->power+power;
string unitType("B");
this->unitName=this->powerToUnit(this->power,unitType);
}

int procmeminfo::update() {
ifstream file("/proc/meminfo");
string token;
long param;
string unit;
string line="";
int l;
class sizeEntry *se=NULL;

int lines=0;

if(!file.is_open())
	throw fileerror();

while(std::getline(file,line)){
		stringstream ss(line);
		unit="";
		param=-1;
		ss >> token >> param;
		ss >> unit;
		l=token.length();
		if(token[l-1]==':')
			token.erase(l-1,1);

		se=new class sizeEntry(param,unit);
		info[token]=se;
		++lines;
}
return lines;
}

class sizeEntry* procmeminfo::get(string& name) {
	sizeEntry *rv=info[name];
	rv->ref();
	return rv;
}

void procmeminfo::dump() {
map<string,sizeEntry *>::iterator it;

cout << "Memory info:" << endl;
for(it=info.begin();it!=info.end();++it){
	cout << "\t" << it->first << "= " << (it->second)->getSize() << (it->second)->getUnitName() <<
			"(" << (it->second)->realValue() << ")" << endl;
}
}
