/*
 * procstat.h
 *
 *  Created on: 9 Jun 2014
 *      Author: andy
 */

#ifndef PROCSTAT_H_
#define PROCSTAT_H_

#include "procfile.h"
#include <vector>
#include <time.h>
#include "metrixdb.h"

using namespace std;

class valueNotPresentException: public exception {
	virtual const char * what() const throw()
		{
		return "Unable to open /proc/stat";
		}
}; //valueNotPresentException

class cpustat: public base {
public:
	int getGuest() const {
		if(guest==-1) throw valueNotPresentException();
		return guest;
	}

	void setGuest(int guest) {
		this->guest = guest;
	}

	int getGuestNice() const {
		if(guest_nice==-1) throw valueNotPresentException();
		return guest_nice;
	}

	void setGuestNice(int guestNice) {
		guest_nice = guestNice;
	}

	int getIdle() const {
		if(idle==-1) throw valueNotPresentException();
		return idle;
	}

	void setIdle(int idle) {
		this->idle = idle;
	}

	int getIowait() const {
		if(iowait==-1) throw valueNotPresentException();
		return iowait;
	}

	void setIowait(int iowait) {
		this->iowait = iowait;
	}

	int getIrq() const {
		if(irq==-1) throw valueNotPresentException();
		return irq;
	}

	void setIrq(int irq) {

		this->irq = irq;
	}

	int getNice() const {
		if(nice==-1) throw valueNotPresentException();
		return nice;
	}

	void setNice(int nice) {
		this->nice = nice;
	}

	int getSoftirq() const {
		if(softirq==-1) throw valueNotPresentException();
		return softirq;
	}

	void setSoftirq(int softirq) {
		this->softirq = softirq;
	}

	int getSteal() const {
		if(steal==-1) throw valueNotPresentException();
		return steal;
	}

	void setSteal(int steal) {
		this->steal = steal;
	}

	int getSystem() const {
		if(system==-1) throw valueNotPresentException();
		return system;
	}

	void setSystem(int system) {
		this->system = system;
	}

	int getUser() const {
		if(user==-1) throw valueNotPresentException();
		return user;
	}

	void setUser(int user) {
		this->user = user;
	}

	int db_commit(DB_REF reference,std::string type,int n)
	{
		stringstream idstream;
		idstream << "cpu";
		if(n>0){
			idstream << n;
		}
		idstream << "_";
		string id;
		id=idstream.str()+"user";
		reference.insert(type,id,user);
		id=idstream.str()+"system";
		reference.insert(type,id,system);
		id=idstream.str()+"nice";
		reference.insert(type,id,nice);
		id=idstream.str()+"idle";
		reference.insert(type,id,idle);
		id=idstream.str()+"iowait";
		reference.insert(type,id,iowait);
		id=idstream.str()+"irq";
		reference.insert(type,id,irq);
		id=idstream.str()+"softirq";
		reference.insert(type,id,softirq);
		id=idstream.str()+"steal";
		reference.insert(type,id,steal);
		id=idstream.str()+"guest";
		reference.insert(type,id,guest);
		id=idstream.str()+"guest_nice";
		reference.insert(type,id,guest_nice);

		return 1;
	}
	void dump()
	{
		cout << "\t\t" << user << "\t" << system << "\t" << nice << "\t" << idle <<  endl;
	}
private:
	int user,nice,system,idle,iowait,irq,softirq,steal,guest,guest_nice;

};

class procstat: public procfile {
public:
	procstat();
	virtual ~procstat();

	void ref();
	int update();
	int db_commit(DB_REF reference);

	void dump();
private:
	void parse_cpu(stringstream &file);

	vector<class cpustat *> cpus;
	int page_in,page_out;
	int swap_page_in,swap_page_out;
	long interrupts_total;
	long soft_interrupts_total;
	int context_switches;
	time_t boot_time;
	long processes_total;
	int procs_running;
	int procs_io_blocked;

};

#endif /* PROCSTAT_H_ */
