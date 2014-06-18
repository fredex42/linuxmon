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

#include "dbpostgres.h"
#include "procstat.h"
#include "procmeminfo.h"
#include "procloadavg.h"

using namespace std;

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

class db_postgres *dbc=NULL;

try{
	if(opts["db_host"]!=""){
		dbc=new db_postgres(opts["db_host"],opts["db_port"],opts["db_user"],opts["db_password"],"metrix");
	} else {
		dbc=new db_postgres("metrix");
	}
}
catch(exception& e){
	cerr << "ERROR: Problem connecting to database: " << e.what() << endl;
	exit(1);
}

class procstat stat=procstat();

stat.update();
stat.dump();

class procmeminfo mi=procmeminfo();
mi.update();
mi.dump();

class procloadavg la=procloadavg();
la.update();
la.dump();

delete dbc;

}



