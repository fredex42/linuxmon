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
