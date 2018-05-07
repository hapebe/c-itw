#!/bin/bash
N=10
if [ $# -gt 0 ] ; then
	N=$1
fi
shuf -i 0-1000 -n $N
