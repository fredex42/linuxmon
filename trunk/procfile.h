/*
 * procfile.h
 *
 *  Created on: 9 Jun 2014
 *      Author: andy
 */

#ifndef PROCFILE_H_
#define PROCFILE_H_

#include "base.h"

class procfile: public base {
public:
	procfile();
	virtual ~procfile();

	int db_commit(DB_REF reference);
};

#endif /* PROCFILE_H_ */
