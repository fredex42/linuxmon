/*
 * base.h
 *
 *  Created on: 9 Jun 2014
 *      Author: andy
 */

#ifndef BASE_H_
#define BASE_H_

#include <ostream>
using namespace std;

#define DB_REF void*

class base {
public:
	base();
	virtual ~base();

	void ref();
	void unref();

	ostream warn;
	ostream debug;
private:
	int refcount;
};

#endif /* BASE_H_ */
