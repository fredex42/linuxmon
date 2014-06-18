/*
 * dbpostgres.h
 *
 *  Created on: 18 Jun 2014
 *      Author: andy
 */

#ifndef DBPOSTGRES_H_
#define DBPOSTGRES_H_

#include <string>
using namespace std;
#include "base.h"
#include <pqxx/pqxx>

class db_postgres: public base {
public:
	/* this constructor connects over TCP/IP */
	db_postgres(const string& host,const string& port,const string& user,const string& pass,const string& dbname);
	/* this connector connectss over local unix socket */
	db_postgres(const string& dbname);
	/* basic constructor */
	db_postgres();

	virtual ~db_postgres();

	void begin();
	void commit();
	void doSQL(const string &sql,...);

private:
	bool needs_commit;
	pqxx::connection *conn;
};

#endif /* DBPOSTGRES_H_ */
