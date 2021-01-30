#!/bin/bash

firewall_pkts=""

while read rule
do
	match_pkts=""

	rule=`echo "$rule" | tr -d ' ' | sed -e 's/#.*//'`
	if [[ "$rule" == "" ]]; then
		continue
	fi
	IFS=',' read -ra rule_array <<< "$rule"
	for filter in "${rule_array[@]}"
	do
    	match_pkts+=`valgrind ./firewall.exe "$filter" < $1`
		match_pkts+="\n"
	done
	firewall_pkts+=`echo -e "${match_pkts}" | sed '/^[[:space:]]*$/d' | sort | uniq -c  | grep -E "^ *${#rule_array[@]} " | sed -e "s/^ *${#rule_array[@]} //"`
	firewall_pkts+="\n"
done 


echo -e "${firewall_pkts}" | sed '/^[[:space:]]*$/d' | tr -d ' ' | sort
