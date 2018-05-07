#!/bin/bash
for i in `seq 1 10000` ; do
	echo $(( ((($RANDOM*1000)+$RANDOM) % 2000000) - 1000000))
done
