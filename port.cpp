#include <iostream>
#include <cstdlib>
#include "port.h"

#define LEN_ARR 2
Port::Port(String pattern):Field(pattern,PORT){}


/* Defines the set of valid values for Port field. */
bool Port::set_value(String val) {
	String *output = NULL;
	size_t *size = new size_t;
	val.split("-", &output, size);

	if (*size != LEN_ARR) {
		delete [] output;
		delete size;
		return false;
	}

	range[0]=(output)[0].trim().to_integer();
	range[1]=(output)[1].trim().to_integer();

	delete [] output;
	delete size;

	if(range[0] > range[1]) {
		return false;
	}
	return true;
}


/* Checks whether val complies with Port field rules. */
bool Port::match_value(String val) const{
	int num_val = val.trim().to_integer();

	if ((num_val < range[0]) && (num_val > range[1])) {
		return false;
	}
	return true;
}

