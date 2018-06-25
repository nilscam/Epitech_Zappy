#!/bin/bash

if [ $# -lt 4 ]
then
	echo "USAGE: $0 IP PORT NB_AI [ teams ... ]"
	exit 0
fi

exe='./zappy_ai'

if [ ! -f "$exe" ]
then
	echo "'$exe' doesn't exist"
	exit 1
fi

ip=$1
port=$2
ai=$3

for ((i=1; i<=$ai; i++))
do
	for team in "${@:4}"
	do
		$exe -p $port -n $team -h $ip &
	done
	
done
