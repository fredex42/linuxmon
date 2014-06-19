/*
 * dbpostgres.cpp
 *
 *  Created on: 18 Jun 2014
 *      Author: andy
 */

#include "dbpostgres.h"
#include <stdarg.h>

using namespace pqxx;

db_postgres::~db_postgres() {
	cerr << "DEBUG: Shutting down database connection" << endl;
	if(needs_commit) this->commit();
	if(conn) delete conn;
}

db_postgres::db_postgres(const string& host, const string& port,const string& user,
		const string& pass, const string& dbname) {
string connectionString;

transaction=NULL;
connectionString="host="+host+" user="+user+" password="+pass+" dbname="+dbname;
if(port!=""){
	connectionString+=" port="+port;
}

cerr << "DEBUG: postgres connection string='"<<connectionString<<"'\n";

conn=new connection(connectionString);
needs_commit=false;
}

db_postgres::db_postgres(const string& dbname) {
conn=new connection("dbname="+dbname);
needs_commit=false;
transaction=NULL;
}

db_postgres::db_postgres() {
conn=NULL;
transaction=NULL;
needs_commit=false;
}

void db_postgres::begin() {
if(transaction!=NULL)
	throw connectionBusyException();

transaction=new pqxx::work(*(this->conn),"DatabaseTransaction");
needs_commit=true;
}

void db_postgres::commit() {
if(transaction==NULL){
	needs_commit=false;
	return;
}

transaction->commit();
delete transaction;
transaction=NULL;
needs_commit=false;
}

void db_postgres::doSQL(const string &sql)
{
bool should_close=false;
if(transaction==NULL){
	this->begin();
	should_close=true;
}
result=transaction->exec(sql);

if(should_close)
	this->commit();

}

/*
void db_postgres::doSQL(const string &sql,...) {
va_list args;

va_start(args,sql);

va_end(args);

}
*/
