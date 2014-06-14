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

using namespace std;

class cpustat: public base {
public:
	int getGuest() const {
		return guest;
	}

	void setGuest(int guest) {
		this->guest = guest;
	}

	int getGuestNice() const {
		return guest_nice;
	}

	void setGuestNice(int guestNice) {
		guest_nice = guestNice;
	}

	int getIdle() const {
		return idle;
	}

	void setIdle(int idle) {
		this->idle = idle;
	}

	int getIowait() const {
		return iowait;
	}

	void setIowait(int iowait) {
		this->iowait = iowait;
	}

	int getIrq() const {
		return irq;
	}

	void setIrq(int irq) {
		this->irq = irq;
	}

	int getNice() const {
		return nice;
	}

	void setNice(int nice) {
		this->nice = nice;
	}

	int getSoftirq() const {
		return softirq;
	}

	void setSoftirq(int softirq) {
		this->softirq = softirq;
	}

	int getSteal() const {
		return steal;
	}

	void setSteal(int steal) {
		this->steal = steal;
	}

	int getSystem() const {
		return system;
	}

	void setSystem(int system) {
		this->system = system;
	}

	int getUser() const {
		return user;
	}

	void setUser(int user) {
		this->user = user;
	}

	int db_commit(DB_REF reference);
private:
	int user,nice,system,idle,iowait,irq,softirq,steal,guest,guest_nice;

};

class fileerror: public exception
{
	virtual const char * what() const throw()
		{
		return "Unable to open /proc/stat";
		}
};// fileerror;

class procstat: public procfile {
public:
	procstat();
	virtual ~procstat();

	void ref();
	int update();
	int db_commit(DB_REF reference);

private:
	void parse_cpu(ifstream &file);

	vector<class cpustat *> cpus;
	int page_in,page_out;
	int swap_page_in,swap_page_out;
	int context_switches;
	int boot_time;
	long processes_total;
	int procs_running;
	int procs_io_blocked;

};

#endif /* PROCSTAT_H_ */
