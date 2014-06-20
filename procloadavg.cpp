/*
 * procloadavg.cpp
 *
 *  Created on: 18 Jun 2014
 *      Author: andy
 */

#include "procloadavg.h"
#include "metrixdb.h"

procloadavg::procloadavg() {
	// TODO Auto-generated constructor stub
	this->metrictype="load";
	fifteen_min=-1;
	total_entities=-1;
	one_min=-1;
	five_min=-1;
	last_pid=-1;
	runnable_entities=-1;

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

int procloadavg::db_commit(DB_REF reference)
{
string id;
id="1min";
reference.insert(metrictype,id,one_min);
id="5min";
reference.insert(metrictype,id,five_min);
id="15min";
reference.insert(metrictype,id,fifteen_min);
id="total_entities";
reference.insert(metrictype,id,total_entities);
id="runnable_entities";
reference.insert(metrictype,id,runnable_entities);

}

void procloadavg::dump() {
	cout << "Load Average information:";
	cout << "\t1 minute: " << one_min << "; 5 minute " << five_min << "; 15 minute " << fifteen_min << endl;
	cout << "Total scheduling entities=" << total_entities << " of which runnable=" << runnable_entities << "("
			<< (float)runnable_entities/(float)total_entities << ")" << endl;

}
