/*
 * procstat.cpp
 *
 *  Created on: 9 Jun 2014
 *      Author: andy
 */

#include "procstat.h"
#include "metrixdb.h"

using namespace std;

procstat::procstat() {
	// TODO Auto-generated constructor stub
	page_in=-1;
	page_out=-1;
	swap_page_in=-1;
	swap_page_out=-1;
	soft_interrupts_total=-1;
	interrupts_total=-1;
	context_switches=-1;
	boot_time=-1;
	processes_total=-1;
	procs_running=-1;
	procs_io_blocked=-1;
	metrictype="system";
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
			ss >> this->page_in >> this->page_out;
		} else if(token=="swap"){
			ss >> this->swap_page_in >> this->swap_page_out;
		} else if(token=="intr"){
			/* FIXME: this only reads the total. Should read interrupts into a seperate structure, like cpus */
			ss >> interrupts_total;
		} else if(token=="softirq"){
			ss >> soft_interrupts_total;
		} else if(token=="disk_io"){

		} else if(token=="ctxt"){
			ss >> context_switches;
		} else if(token=="btime"){
			ss >> boot_time;
		} else if(token=="processes"){
			ss >> processes_total;
		} else if(token=="procs_running"){
			ss >> procs_running;
		} else if(token=="procs_blocked"){
			ss >> procs_io_blocked;
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

cout << "\t" << "Pages in: " << page_in << " out: " << page_out << endl;
cout << "\t" << "Pages brought in from swap: " << swap_page_in << " out: " << swap_page_out << endl;
cout << "\t" << "Total number of interrupts serviced: " << interrupts_total << endl;
cout << "\t" << "Soft IRQs serviced: " << soft_interrupts_total << endl;
cout << "\t" << "Context switches: " << context_switches << endl;
cout << "\t" << "Boot time: " << ctime(&boot_time) << endl;
cout << "\t" << "Total number of processes launched: " << processes_total << endl;
cout << "\t" << "Processes currently in a runnable state: " << procs_running << endl;
cout << "\t" << "Processes waiting for IO: " << procs_io_blocked << endl;

}

int procstat::db_commit(DB_REF reference)
{
vector<cpustat *>::iterator it;
int n=0;
for(it=cpus.begin();it!=cpus.end();++it){
	(*it)->db_commit(reference,metrictype,n);
	++n;
}

string id;
id="pages_in";
reference.insert(metrictype,id,page_in);
id="pages_out";
reference.insert(metrictype,id,page_out);
id="swap_page_in";
reference.insert(metrictype,id,swap_page_in);
id="swap_page_out";
reference.insert(metrictype,id,swap_page_out);
id="interrupts_total";
reference.insert(metrictype,id,interrupts_total);
id="soft_interrupts_total";
reference.insert(metrictype,id,soft_interrupts_total);
id="context_switches";
reference.insert(metrictype,id,context_switches);
id="boot_time";
reference.insert(metrictype,id,boot_time);
id="processes_launched";
reference.insert(metrictype,id,processes_total);
id="procs_runnable";
reference.insert(metrictype,id,procs_running);
id="procs_io_blocked";
reference.insert(metrictype,id,procs_io_blocked);
return 1;
}
