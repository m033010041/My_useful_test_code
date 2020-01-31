#!/bin/bash

while true;
do
	counter=$(<counter.txt)
	echo "$counter"

	sleep 1
	counter=$((counter+1))
	echo "$counter" > counter.txt
	echo "write counter"
done
