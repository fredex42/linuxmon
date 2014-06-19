/*
 * serverparams.cpp
 *
 *  Created on: 19 Jun 2014
 *      Author: andy
 */

#include <malloc.h>
#include <arpa/inet.h>
#include <string.h>
#include <sys/types.h>
#include <ifaddrs.h>
#include <sstream>
//#include <iostream>
#include <unistd.h>

#include "serverparams.h"

serverparams::serverparams() {
	// TODO Auto-generated constructor stub
update();
}

serverparams::~serverparams() {
	// TODO Auto-generated destructor stub
}

ipv4::ipv4() {
address=new struct sockaddr_in;
memset(this->address,0,sizeof(struct sockaddr_in));
}

ipv4::ipv4(struct sockaddr_in* addr) {
	address=new struct sockaddr_in;
	this->set(addr);
}

void ipv4::set(struct sockaddr_in* addr) {
	if(!addr)
		throw invalidArgumentException("ipv4::ipv4: you must pass in a valid address");
	if(addr->sin_family!=AF_INET){
		std::stringstream ss;
		ss << "ipv4::ipv4: the given address is not IPV4. Class was " << addr->sin_family;
		std::string msg=ss.str();
		throw invalidArgumentException(msg);
	}

	memcpy(this->address,addr,sizeof(struct sockaddr_in));
}

ipv4::~ipv4() {
free(this->address);
}

struct sockaddr_in* ipv4::as_address() {
struct sockaddr_in* rtn=new struct sockaddr_in;
memcpy(rtn,address,sizeof(struct sockaddr_in));

return rtn;
}

std::string& ipv4::as_string() {
char *tmp=(char *)malloc(INET_ADDRSTRLEN);
std::string *rtn=new std::string;

memset(tmp,0,INET_ADDRSTRLEN);

inet_ntop(address->sin_family,(const void *)&(address->sin_addr),tmp,INET_ADDRSTRLEN);
tmp[INET_ADDRSTRLEN]=0;

*rtn=tmp;
return *rtn;
}

void ipv4::first_available() {
struct ifaddrs* adrlist=NULL,*entry=NULL;

getifaddrs(&adrlist);

entry=adrlist;
do{
	try {
		//exclude loopback interface
		if(((struct sockaddr_in *)(entry->ifa_addr))->sin_addr.s_addr==htonl(INADDR_LOOPBACK))
			continue;

		this->set((struct sockaddr_in *)(entry->ifa_addr));
		//cerr << "got address: " << this->as_string() << "with family " << this->family() << endl;
		break;
	}
	catch(invalidArgumentException& e){
		/* we get this exception if the address isn't defined as an ipv4 address, so continue going */
		//cerr << "Debug: " << e.what() << endl;
	}
} while(entry=entry->ifa_next);

}

int ipv4::family() {
	return (int)(address->sin_family);
}

std::string& serverparams::get(std::string& name) {
}

#ifndef BUFSIZE
#define BUFSIZE 512
#endif

void serverparams::update() {
ipv4 my_ip;
/*get the first available IPv4 address that isn't a loopback*/
my_ip.first_available();
value["ip_address"]=my_ip.as_string();

char tmp[BUFSIZE];
gethostname(tmp,BUFSIZE);
std::string tmp2(tmp);	/*convert to an STL string to go into the map*/
value["server_name"]=tmp2;

}

void serverparams::dump() {
std::map<std::string,std::string>::iterator it;

cout << "Server parameters:" << endl;
	for(it=value.begin();it!=value.end();++it){
		cout << "\t" << it->first << " = " << it->second << endl;
	}
}

