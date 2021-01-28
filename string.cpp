
#include "string.h"
#include <iostream>
#include <cstring>
#include "ip.h" 

#define MIN_INT 0
#define MAX_INT 255
#define MAX_SHIFT 24
#define BITS_IN_BYTE 8

using namespace std;


/* Initiates an empty string: equate to zero data and length. */
String::String() {
    data = NULL;
    length = 0;
}


/* Initiates string from other string.
 * Update the internal fields: data and length. */
String::String(const String &str) {
    length = str.length;
    if (0 == length)
	{
		data = NULL;
	} else{
    data = new char[length+1];
    strcpy(data,str.data);
	}
}


/* Initiates a string from char array.
 * Update the internal fields: data and length. */
String::String(const char *str) {
	if (str == NULL)
	{
		data = NULL;
		length = 0;
		return;
	}
    length = strlen(str);
    data = new char[length+1];
    strcpy(data, str);
}


/* String destractor */
String::~String(){
	delete[] data;
}


/* Overriding the contents of the current string by a string */
String& String::operator=(const String &rhs) {
	if ((data != NULL) || (rhs.length == 0)) {
		delete[] data;
	} else {
     	length = rhs.length;
        data = new char[length+1];
        strcpy(data, rhs.data);
    }
    return *this;
}


/* Overriding the contents of the current string by a char array */
String& String::operator=(const char *str) {
	if (str==NULL) {
		data = NULL;
		length = 0;
	} else {
		if (data!=NULL){
			delete [] data;
		}
        length = strlen(str);
        data = new char[length+1];
        strcpy(data, str);
    }
	return *this;
}


/* Returns true if the inner fields match those of the rhs String.
 * Else, return false. */
bool String::equals(const String &rhs) const {
    if (length != rhs.length) {
        return false;
    } else {
        return (strcmp(data, rhs.data) ? false : true);
    }
}

/* Return of true if the inner fields match the value of the char array 
 * and its length. Else, return false. */
bool String::equals(const char *rhs) const {
    if ((length != strlen(rhs)) || (rhs == NULL)) {
        return false;
    } else {
        return (strcmp(data, rhs) ? false : true);
    }
}

/**
 * @brief Splits this to several sub-strings according to delimiters.
 * Allocates memory for output that the user must delete (using delete[]).
 * @note Does not affect this.
 * @note If "output" is set to NULL, do not allocated memory, only
 * compute "size".
 */
void String::split(const char *delimiters, String **output, size_t *size) const {
    size_t sub_amount = 0;
    size_t delimiters_length = strlen(delimiters);
    char temp[length + 1] = {0};
    int index_to_tmp = 0;

    if ((NULL == delimiters) || (NULL == data)) {
   		return;
	}

	strcpy(temp, data);
	temp[length] = '\0';

    for (size_t i=0; i < length; i++) {
        for (size_t j=0; j <delimiters_length; j++) {
            if (data[i] == delimiters[j]) {
            	sub_amount++;
            }
        }
    }
    *size = sub_amount+1;
    if (output == NULL){
    	return;
    }
    *output = new String[sub_amount+1];
    sub_amount=0;
    for (size_t i=0; i < length; i++) {
       for (size_t j=0; j < delimiters_length; j++) {
           if (data[i] == delimiters[j]) {
            	temp[i] = '\0';
            	(*output)[sub_amount] = String(&temp[index_to_tmp]);
            	sub_amount++;
            	index_to_tmp = i + 1;
            }
        }
    }
    (*output)[sub_amount] = String(&temp[index_to_tmp]);
    return;
}

/* Remove leading or trailing white-spaces without change this. */
String String::trim() const {
    int space_start = 0;
    int space_end = length;
    for (size_t i=space_start; i<length; i++) {    /* Leading white-spaces */
        if (data[i] == ' ') {
            space_start += 1;
        } else {
            i = length;
        }
    }
    for (int j=space_end; j>=0; j--) {    /* Trailing white-spaces */
        if (data[j] == ' ') {
            space_end -= 1;
        } else {
            j = -1;
        }
    }
    size_t new_length = space_end - space_start + 1;
    char *temp = new char[new_length + 1];
    strncpy(temp, &data[space_start], new_length);
    temp[new_length] = '\0';
    return String(temp);
}


/* convert String to an integer. */
int String::to_integer() const {
    int convert = 0;
    String* sub_strings = NULL;
    size_t size = 0;

    split(".", &sub_strings, &size);
    /* size = 4 => data represents an IP address.
     * Ip format: ad.cd.xy.zw, thus we get 4 sub-strings. */
    if(size == SEGMENTS) {
        /* For each sub-string:
         * (1) Remove leading or trailing spaces.
         * (2) Convert to integer.                  */
        for(size_t i=0; i < size; i++) {
            /* Each Byte in integer is decimally represented  */
            int byte = sub_strings[i].trim().to_integer();
            if ((byte > MAX_INT) || (byte < MIN_INT)) {
                delete[] sub_strings;
                return 0;  
            }
            /* ab.cd.xy.zw => ab << 24 | cd << 16 | xy << 8 | zw << 0 */
            int location = MAX_SHIFT - (i * BITS_IN_BYTE);
            convert |= byte << location;
        }
    } else {    /* The number is represented by ascii value  */
        convert = atoi(data);
    }
    delete[] sub_strings;
    return convert;
}