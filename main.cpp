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

#include "procstat.h"
#include "procmeminfo.h"
#include "procloadavg.h"

using namespace std;

std::map<std::string,std::string> opts;
typedef std::map<std::string,std::string>::iterator options_iterator;

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
int n_opts=parse_options(argc,argv);

/*
cerr << "debug: " << n_opts << " options provided: " << endl;
for(options_iterator i=opts.begin();i!=opts.end();++i){
	cerr << "\t" << i->first << "=" << i->second << endl;
}
*/

class procstat stat=procstat();

stat.update();
stat.dump();

class procmeminfo mi=procmeminfo();
mi.update();
mi.dump();

class procloadavg la=procloadavg();
la.update();
la.dump();

}



