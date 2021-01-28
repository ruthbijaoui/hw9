#include "ip.h"
#include <cstring>
#include <iostream>

#define NUM_OF_BIT 32
#define MAX_NUM 0xFFFFFFFF

Ip::Ip(String pattern): Field(pattern, IP){}


/* Defines the set of valid values for IP field. */
bool Ip::set_value(String val) {	
	String *output;
	size_t size = 0;
	val.split("/", &output, &size);

	if (size != MASK_SEGMENT){
		delete[] output;
		return false;
	}
	int mask = (output)[1].trim().to_integer();

	if ((mask < 0) || (mask > NUM_OF_BIT)) {
		delete[] output;
		return false;
	}
	int ip = (output)[0].trim().to_integer();
	int n = NUM_OF_BIT - mask;
	unsigned int Helpmask = (n == NUM_OF_BIT) ? MAX_NUM :((unsigned int)1 << n) - 1;
	low = ip & (~Helpmask);
	high = ip | Helpmask;
	delete[] output;
	return true;
}


/* Checks whether val complies with IP field rules. */
bool Ip::match_value(String val) const {
	unsigned int NumVal = (unsigned int)val.trim().to_integer();
	if ((NumVal >= low) && (NumVal <= high)) {
		return true;
	}
	return  false;
}

	
