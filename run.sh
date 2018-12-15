#!/bin/bash
file="server"
if [ -f "$file" ]
then
	./server 4000
else
	make && ./server 4000
fi

