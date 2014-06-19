/*
 * metrixdb.h
 *
 *  Created on: 19 Jun 2014
 *      Author: andy
 */

#ifndef METRIXDB_H_
#define METRIXDB_H_

#include <string>
#include "dbpostgres.h"

class metrixdb: public db_postgres {
public:
	metrixdb();
	virtual ~metrixdb();

	void insert(std::string& type,std::string& identifier,std::string& value);

	int server_by_name(std::string& server_name);

private:
};

#endif /* METRIXDB_H_ */
