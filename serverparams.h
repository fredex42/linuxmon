/*
 * serverparams.h
 *
 *  Created on: 19 Jun 2014
 *      Author: andy
 */

#ifndef SERVERPARAMS_H_
#define SERVERPARAMS_H_

#include <string>
#include <map>
#include <sys/types.h>

#include "base.h"

#ifndef INADDR_LOOPBACK
#define       INADDR_LOOPBACK         (u_long)0x7F000001
#endif

class ipv4: public base {
public:
	ipv4();
	ipv4(struct sockaddr_in *);
	~ipv4();

	void set(struct sockaddr_in *);

	struct sockaddr_in *as_address();
	std::string& as_string();

	void first_available();
	int family();

private:
	struct sockaddr_in* address;

};
class serverparams: public base {
public:
	serverparams();
	virtual ~serverparams();

	std::string& get(std::string& name);
	std::string& get(char *name);
	void update();

	void dump();
private:
	std::map<std::string,std::string> value;
};

#endif /* SERVERPARAMS_H_ */
