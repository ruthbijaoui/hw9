#include <iostream>
#include <cstring>

#include "field.h"
#include "port.h"
#include "ip.h"

#define NUM_TO_SPLIT 12 

using namespace std;


Field::Field(String pattern, field_type type)
:pattern(pattern),type(type){}


Field::Field(String pattern)
:	pattern(pattern) {
	type = GENERIC;
}


/* Field destractor */
Field::~Field(){}

    
field_type Field::get_type() const {
	return type;
}


/* Defines the set of valid values for the field. */
bool Field::set_value(String val) {
	if (type == IP) {
		return (((Ip*)this)->set_value(val));
	} else if(type == PORT) {
		return ((Port*)this)->set_value(val);
	}
	return false;
}


/* Checks whether a parameter value complies with the field rules. */
bool Field::match_value(String val) const {
	if (type == IP) {
		return ((Ip*)this)->match_value(val);
	} else if(type == PORT) {
		return ((Port*)this)->match_value(val);
	}
	return false;
}


/* Checks whether a string of fackets complies with the field rules. */
bool Field::match(String packet) {
	String *output;
	size_t size = 0;
	bool ans = false;

	packet.split(",-=", &output, &size);
	if (size != NUM_TO_SPLIT) {
		return false;
	}
	for (size_t i=0; i < size; i++) {
		if (((output[i]).trim().equals("port"))&&(type)){
			ans=match_value((output)[i+1].trim());

		} else if (((output[i]).trim().equals("ip"))&&(!(this->type))) {
			ans=match_value((output)[i+1].trim());
		}
		if (ans) {
			delete[] output;
			return ans;
		}
	}
	delete[] output;
	return ans;
}



