/*
 * main.cpp
 *
 *  Created on: 11 Jun 2014
 *      Author: andy
 */

#include <iostream>
#include <map>
#include <string>
#include <string.h>
#include <getopt.h>
#include <iostream>

#include "base.h"
#include "metrixdb.h"
#include "procstat.h"
#include "procmeminfo.h"
#include "procloadavg.h"
#include "serverparams.h"

using namespace std;

#define nodb	//define this for testing. It will skip attempting to connect to db.

std::map<std::string,std::string> opts;
typedef std::map<std::string,std::string>::iterator options_iterator;

/*hint: metrixinsert:metrixinsert */

int load_config(const string& filename)
{
ifstream file(filename.c_str());
string line;
int bp=-1;
int n=0;
string key,val;

if(!file.is_open()){
	cerr << "ERROR: Unable to open config file " << filename << endl;
	return 0;
}

while(std::getline(file,line)){
	if(line[0]=='#')
		continue;
	bp=line.find('=');
	if(bp==-1)
		continue;
	key=line.substr(0,bp);
	val=line.substr(bp+1);
	opts[key]=val;
	++n;
}
return n;
}

int parse_options(int argc,char **argv)
{
/*
int c;
static struct option long_options[]={
		{ "dbhost", required_argument,0,'h' },
		{ "dbuser", required_argument,0,'u' },
		{ "dbpass", required_argument,0,'p' },
		{ "dbport", required_argument,0,'n' }
};


while(1){
	int option_index=0;
	c=getopt_long(argc,argv,"hupn",long_options,&option_index);

}
*/
string argname,value;
int n,nopts=0;
/* arg 0 is the program name */

for(n=1;n<argc;n+=2){
	if(n+1>argc) break;
	if(strlen(argv[n])<2) continue;
//	cerr << "debug: got arg " << argv[n] << "\n";
	if(argv[n][0]=='-'){
		if(argv[n][1]=='-'){
			argname=(char *)&argv[n][2];
		} else {
			argname=(char *)&argv[n][1];
		}
		value=argv[n+1];
		opts[argname]=value;
		++nopts;
	} else {
		continue;
	}
}
return nopts;
}

int main(int argc,char *argv[])
{
int c_opts=load_config("/etc/linuxmon.cfg");

int n_opts=parse_options(argc,argv);


cerr << "debug: " << n_opts << " options provided: " << endl;
for(options_iterator i=opts.begin();i!=opts.end();++i){
	cerr << "\t" << i->first << "=" << i->second << endl;
}

class metrixdb *dbc=NULL;

#ifndef nodb
try{
	if(opts["db_host"]!=""){
		dbc=new metrixdb(opts["db_host"],opts["db_port"],opts["db_user"],opts["db_password"],"metrix");
	} else {
		dbc=new metrixdb("metrix");
	}
}
catch(exception& e){
	cerr << "ERROR: Problem connecting to database: " << e.what() << endl;
	//exit(1);
}
#endif

class serverparams sp;
/*class ipv4 address;
address.first_available();
cout << "Got first available address: " << address.as_string();
*/
sp.dump();

#ifndef nodb
int server_id=dbc->server_by_params(sp);
cout << "Got server id: " << server_id << endl;

dbc->begin();
#endif

class procstat stat=procstat();
stat.update();
stat.dump();
#ifndef nodb
stat.db_commit(*dbc);
#endif

class procmeminfo mi=procmeminfo();
mi.update();
mi.dump();
#ifndef nodb
mi.db_commit(*dbc);
#endif

class procloadavg la=procloadavg();
la.update();
la.dump();
#ifndef nodb
la.db_commit(*dbc);
#endif

dbc->commit();

delete dbc;

}



