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
#include "serverparams.h"
class metrixdb: public db_postgres {
public:
	/* this constructor connects over TCP/IP */
	metrixdb(const string& host,const string& port,const string& user,const string& pass,const string& dbname) :
		db_postgres(host,port,user,pass,dbname){
		server_id=-1;
	}
	/* this connector connectss over local unix socket */
	metrixdb(const string& dbname) : db_postgres(dbname){
		server_id=-1;
	}
	/* basic constructor */
	metrixdb() : db_postgres(){
		server_id=-1;
	}

	virtual ~metrixdb();

	void insert(std::string& type,std::string& identifier,std::string& value);
//	void insert(std::string& type,std::string& identifier,int value);
	void insert(std::string& type,std::string& identifier,float value);

	int server_by_name(std::string& server_name);
	int server_by_params(serverparams& params);
private:
	int server_id;
};

#endif /* METRIXDB_H_ */
