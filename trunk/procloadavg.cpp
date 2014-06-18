/*
 * procloadavg.cpp
 *
 *  Created on: 18 Jun 2014
 *      Author: andy
 */

#include "procloadavg.h"

procloadavg::procloadavg() {
	// TODO Auto-generated constructor stub

}

procloadavg::~procloadavg() {
	// TODO Auto-generated destructor stub
}

int procloadavg::update() {
ifstream file("/proc/loadavg");
string entities;

if(!file.is_open())
	throw fileerror();

/*while(std::getline(file,line)){
		stringstream ss(line);
		unit="";
		param=-1;
		ss >> token >> param;
		ss >> unit;
		*/
file >> one_min >> five_min >> fifteen_min >> entities >> last_pid;
if(entities.length()>0){
	sscanf(entities.c_str(),"%d/%d",&runnable_entities,&total_entities);
}

return 1;

}

void procloadavg::dump() {
	cout << "Load Average information:";
	cout << "\t1 minute: " << one_min << "; 5 minute " << five_min << "; 15 minute " << fifteen_min << endl;
	cout << "Total scheduling entities=" << total_entities << " of which runnable=" << runnable_entities << "("
			<< (float)runnable_entities/(float)total_entities << ")" << endl;

}
