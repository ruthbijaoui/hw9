#include <iostream>
#include <cstring>
#include "ip.h"
#include "port.h"

extern int check_args(int, char**);
extern void parse_input(Field&);


int main(int argc, char** argv) {
	
	String* output;
	size_t size = 0;
	
	/* Check that the parameters of main method are correct */
	if (check_args(argc, argv) != 0) {
		return -1;
	}
	String new_rule(argv[1]); 
	new_rule.split("=", &output, &size);
	String new_rule_name(output[0].trim());
	String new_rule_val(output[1].trim());
	
	/* Check if the command is IP */
	if ((new_rule_name.equals("src-ip")) || (new_rule_name.equals("dst-ip"))) { 
		Ip ip(new_rule_name);	
		ip.set_value(new_rule_val);
		parse_input(ip);    /* Receives a reference to IP objects */
	}					    /* and print the captured packets that */
						    /* meet the defined rules. */
	/* Check if the command is port */
	if((new_rule_name.equals("src-port")) || (new_rule_name.equals("dst-port"))) { 
		Port port(new_rule_name);
		port.set_value(new_rule_val);
		parse_input(port);    /* Receives a reference to port objects */
	}					  	  /* and print the captured packets that */
	delete[] output;		  /* meet the defined rules. */
	return 0;
}


