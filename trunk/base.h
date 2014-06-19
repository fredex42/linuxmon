/*
 * base.h
 *
 *  Created on: 9 Jun 2014
 *      Author: andy
 */

#ifndef BASE_H_
#define BASE_H_

#include <iostream>
using namespace std;

#define DB_REF void*

class invalidArgumentException: public std::exception {
public:
	invalidArgumentException() {
		desc="An invalid argument was given";
	}
	invalidArgumentException(char *msg){
		desc=msg;
	}

	invalidArgumentException(std::string& msg){
		desc=msg;
	}

	virtual ~invalidArgumentException() throw(){

		}

	virtual const char* what() const throw()
	{
		return desc.c_str();
	}
private:
	std::string desc;
};

/*
template<class T>
class warnstream : public ostream {
public:

class warnstream& operator<<(const T& obj)
{
	std::cout << obj;
	return this;
}
};

template<class T>
class debugstream : public ostream {
public:
	class debugstream& operator<<(const T& obj)
	{
		std::cout << obj;
		return this;
	}
	void output(bool flag){
		should_output=flag;
	}
	bool output(){
		return should_output;
	}
private:
	bool should_output;
};
*/

/*
class MyStreamBuf: public streambuf
{
};
class debugstream : public ostream {
public:
	debugstream() : std::ostream(&msb),ios(0) {}
	virtual ~debugstream() { msb.pubsync(); }


private:
	class MyStreamBuf msb;

};
*/

#define warn std::cerr
#define debug std::cout

class base {
public:
	base();
	virtual ~base();

	void ref();
	void unref();

/*	class warnstream warn;
	class debugstream debug;
	*/
private:
	int refcount;
};

#endif /* BASE_H_ */
