/*
 * procstat.cpp
 *
 *  Created on: 9 Jun 2014
 *      Author: andy
 */

#include <iostream>
#include <fstream>
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

void procstat::parse_cpu(ifstream file)
{

}
int procstat::update()
{
ifstream file("/proc/stat");
string token;
string param;

if(!file.is_open())
	throw fileerror;

while(!file.eof()){
		file >> token;
		this->debug << "Got token: " << token;
		if(token=="cpu"){
			this->parse_cpu(file);
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
			this->warn << "Unrecognised token parsing /proc/stat: " << token;
			//file.getline();
			file >> param >> "\n";
		}
}
return 1;
}
