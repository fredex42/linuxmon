/*
 * procloadavg.h
 *
 *  Created on: 18 Jun 2014
 *      Author: andy
 */

#ifndef PROCLOADAVG_H_
#define PROCLOADAVG_H_

#include "procfile.h"

class procloadavg: public procfile {
public:
	procloadavg();
	virtual ~procloadavg();

	int update();
	int db_commit(DB_REF reference);

	void dump();

	float getFifteenMin() const {
		return fifteen_min;
	}

	void setFifteenMin(float fifteenMin) {
		fifteen_min = fifteenMin;
	}

	float getFiveMin() const {
		return five_min;
	}

	void setFiveMin(float fiveMin) {
		five_min = fiveMin;
	}

	pid_t getLastPid() const {
		return last_pid;
	}

	void setLastPid(pid_t lastPid) {
		last_pid = lastPid;
	}

	float getOneMin() const {
		return one_min;
	}

	void setOneMin(float oneMin) {
		one_min = oneMin;
	}

	int getRunnableEntities() const {
		return runnable_entities;
	}

	void setRunnableEntities(int runnableEntities) {
		runnable_entities = runnableEntities;
	}

	int getTotalEntities() const {
		return total_entities;
	}

	void setTotalEntities(int totalEntities) {
		total_entities = totalEntities;
	}

private:
	float one_min;
	float five_min;
	float fifteen_min;
	int runnable_entities;
	int total_entities;
	pid_t last_pid;
};

#endif /* PROCLOADAVG_H_ */
