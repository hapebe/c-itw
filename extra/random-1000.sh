#!/bin/bash
for i in `seq 1 1000` ; do
	echo $(( ($RANDOM % 2000) - 1000))
done
