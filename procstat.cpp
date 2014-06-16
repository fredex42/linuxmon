/*
 * procstat.cpp
 *
 *  Created on: 9 Jun 2014
 *      Author: andy
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "procstat.h"
using namespace std;

procstat::procstat() {
	// TODO Auto-generated constructor stub
	page_in=-1;
	page_out=-1;
	swap_page_in=-1;
	swap_page_out=-1;
	context_switches=-1;
	boot_time=-1;
	processes_total=-1;
	procs_running=-1;
	procs_io_blocked=-1;
}

procstat::~procstat() {
	// TODO Auto-generated destructor stub
	for(vector<class cpustat *>::iterator i=cpus.begin();i!=cpus.end(); ++i){
		(*i)->unref();
	}
}

#define CPULINE 12
void procstat::parse_cpu(stringstream &ss)
{
int val[CPULINE],n=0;

for(n=0;n<CPULINE;++n)
	val[n]=-1;
n=0;

while(ss>>val[n]){
	++n;
	if(n>CPULINE) break;
}

cpustat *c=new cpustat;
c->setUser(val[0]);
c->setNice(val[1]);
c->setSystem(val[2]);
c->setIdle(val[3]);
c->setIowait(val[4]);
c->setIrq(val[5]);
c->setSoftirq(val[6]);
c->setSteal(val[7]);
c->setGuest(val[8]);
c->setGuestNice(val[9]);

cpus.push_back(c);

}

int procstat::update()
{
ifstream file("/proc/stat");
string token;
string param;
string line="";

if(!file.is_open())
	throw fileerror();

while(std::getline(file,line)){
		stringstream ss(line);
		ss >> token;
		debug << "Got token: " << token << endl;
		if(token.compare(0,3,"cpu")==0){
			this->parse_cpu(ss);
		} else if(token=="page"){
		} else if(token=="swap"){
		} else if(token=="intr"){
		} else if(token=="disk_io"){
		} else if(token=="ctxt"){
		} else if(token=="btime"){
		} else if(token=="processes"){
		} else if(token=="procs_running"){
		} else if(token=="procs_blocked"){
		} else {
			warn << "Unrecognised token parsing /proc/stat: " << token << endl;
			//file.getline();
			ss >> param;
		}
		//file >> "\n";
}
return 1;
}

void procstat::dump()
{
cout << "procstat::dump" << endl;
cout << "\t" << "Number of CPUs found: " << this->cpus.size()-1 << endl;
cout << "\t\t" << "User" << "\t" << "System" << "\t" << "Nice" << "\tIdle" << endl;

for(vector<cpustat *>::iterator i=cpus.begin();i != cpus.end();++i){
	(*i)->dump();
}


}
