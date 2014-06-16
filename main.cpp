/*
 * main.cpp
 *
 *  Created on: 11 Jun 2014
 *      Author: andy
 */

#include <iostream>
#include "procstat.h"

int main(int argc,char *argv[])
{
class procstat stat=procstat();

stat.update();
stat.dump();
}



