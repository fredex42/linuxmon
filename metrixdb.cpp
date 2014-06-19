/*
 * metrixdb.cpp
 *
 *  Created on: 19 Jun 2014
 *      Author: andy
 */

#include "metrixdb.h"

metrixdb::metrixdb() {
	// TODO Auto-generated constructor stub

}

metrixdb::~metrixdb() {
	// TODO Auto-generated destructor stub
}

void metrixdb::insert(std::string& type, std::string& identifier,
		std::string& value) {
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
	return server_id;
}
cerr << "Not yet implemented add-to-database code" << endl;
throw exception();
}
