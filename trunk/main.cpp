/*
 * main.cpp
 *
 *  Created on: 11 Jun 2014
 *      Author: andy
 */

#include <iostream>
#include "procstat.h"
#include "procmeminfo.h"
#include "procloadavg.h"

int main(int argc,char *argv[])
{
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



