/*
 * metrixdb.cpp
 *
 *  Created on: 19 Jun 2014
 *      Author: andy
 */

#include "metrixdb.h"

metrixdb::~metrixdb() {
	// TODO Auto-generated destructor stub
}

void metrixdb::insert(std::string& type, std::string& identifier,
		std::string& value) {

if(server_id==-1)
	throw invalidArgumentException("metrixdb::insert - you must call server_by_params or server_by_name to identify this server before calling insert");

stringstream ss;
ss << "insert into datapoints(server_id,time,metric_type,identifier,value) values ('" <<
		this->server_id << "'," <<
		"now(),'" <<
		type << "','" <<
		identifier << "','" <<
		value <<
		"')";

doSQL(ss.str());

}
/*
void metrixdb::insert(std::string& type,std::string& identifier,int value)
{
	if(server_id==-1)
		throw invalidArgumentException("metrixdb::insert - you must call server_by_params or server_by_name to identify this server before calling insert");

	stringstream ss;
	ss << "insert into datapoints(server_id,time,metric_type,identifier,value) values ('" <<
			this->server_id << "'," <<
			"now(),'" <<
			type << "','" <<
			identifier << "'," <<
			value <<
			")";

	doSQL(ss.str());

}
*/

void metrixdb::insert(std::string& type,std::string& identifier,float value)
{
	if(server_id==-1)
		throw invalidArgumentException("metrixdb::insert - you must call server_by_params or server_by_name to identify this server before calling insert");

	stringstream ss;
	ss << "insert into datapoints(server_id,time,metric_type,identifier,value) values ('" <<
			this->server_id << "'," <<
			"now(),'" <<
			type << "','" <<
			identifier << "'," <<
			value <<
			")";

	doSQL(ss.str());

}

int metrixdb::server_by_params(serverparams& params) {
int server_id=-1;

string name=params.get("server_name");
server_id=server_by_name(name);

if(server_id==-1){
	if(needs_commit) commit();
	doSQL("insert into servers (ip_address,servername) values ('"+params.get("ip_address")+"','"+params.get("server_name")+"') returning server_id");
	result[0][0].to(server_id);
}
this->server_id=server_id;
return server_id;
}

int metrixdb::server_by_name(std::string& server_name) {
int server_id;

if(server_name.length()<1){
	std::string msg="metrixdb::server_by_name: server_name parameter must not be zero-length";
	throw invalidArgumentException(msg);
}

if(needs_commit) commit();

doSQL("select server_id from servers where servername='"+server_name+"'");
if(result.size()>0){
	result[0][0].to(server_id);
	this->server_id=server_id;
	return server_id;
}
return -1;
}
