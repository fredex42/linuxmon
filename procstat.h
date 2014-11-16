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
	cpustat()
	{
		user=-1;
		nice=-1;
		system=-1;
		idle=-1;
		iowait=-1;
		irq=-1;
		softirq=-1;
		steal=-1;
		guest=-1;
		guest_nice=-1;
		total=0;
	}

	/*
	int getGuest() const {
		if(guest==-1) throw valueNotPresentException();
		return guest;
	}
*/
	float getGuest() const {
		if(guest==-1) throw valueNotPresentException();
		return ((float)guest/(float)total)*100.0;
	}

	void setGuest(int guest) {
		if(this->guest!=-1) total-=this->guest;
		this->guest = guest;
		total+=guest;
	}
/*
	int getGuestNice() const {
		if(guest_nice==-1) throw valueNotPresentException();
		return guest_nice;
	}
*/
	float getGuestNice() const {
		if(guest_nice==-1) throw valueNotPresentException();
		return ((float)guest_nice/(float)total)*100.0;
	}

	void setGuestNice(int guestNice) {
		if(this->guest_nice!=-1) total-=this->guest_nice;
		guest_nice = guestNice;
		total+=guest_nice;
	}

	int getIdle() const {
		if(idle==-1) throw valueNotPresentException();
		return ((float)idle/(float)total)*100.0;
	}

	void setIdle(int idle) {
		if(this->idle!=-1) total-=this->idle;
		this->idle = idle;
		total+=idle;
	}

	int getIowait() const {
		if(iowait==-1) throw valueNotPresentException();
		return ((float)iowait/(float)total)*100.0;
	}

	void setIowait(int iowait) {
		if(this->iowait!=-1) total-=this->iowait;
		this->iowait = iowait;
		total+=iowait;
	}

	int getIrq() const {
		if(irq==-1) throw valueNotPresentException();
		return ((float)irq/(float)total)*100.0;
	}

	void setIrq(int irq) {
		if(this->irq!=-1) total-=this->irq;
		this->irq = irq;
		total+=irq;
	}

	int getNice() const {
		if(nice==-1) throw valueNotPresentException();
		return ((float)nice/(float)total)*100.0;
	}

	void setNice(int nice) {
		if(this->nice!=-1) total-=this->nice;
		this->nice = nice;
		total+=nice;
	}

	int getSoftirq() const {
		if(softirq==-1) throw valueNotPresentException();
		return ((float)softirq/(float)total)*100.0;
	}

	void setSoftirq(int softirq) {
		if(this->softirq!=-1) total-=this->softirq;
		this->softirq = softirq;
		total+=softirq;
	}

	int getSteal() const {
		if(steal==-1) throw valueNotPresentException();
		return ((float)steal/(float)total)*100.0;
	}

	void setSteal(int steal) {
		if(this->steal!=-1) total-=this->steal;
		this->steal = steal;
		total+=steal;
	}

	int getSystem() const {
		if(system==-1) throw valueNotPresentException();
		return ((float)system/(float)total)*100.0;
	}

	void setSystem(int system) {
		if(this->system!=-1) total-=this->system;
		this->system = system;
		total+=system;
	}

	int getUser() const {
		if(user==-1) throw valueNotPresentException();
		return ((float)user/(float)total)*100.0;
	}

	void setUser(int user) {
		if(this->user!=-1) total-=this->user;
		this->user = user;
		total+=user;
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
		cout << "\t\t user:" << getUser() << "%\tsystem:" << getSystem() << "%";
		cout << "\tnice:" << getNice() << "%\tidle:" << getIdle() << "%\tiowait:" << getIowait() << endl;
	}
private:
	int user,nice,system,idle,iowait,irq,softirq,steal,guest,guest_nice;
	int64_t total;
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
