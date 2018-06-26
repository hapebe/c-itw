#!/bin/bash
for filename in ./extra/ip-adressen-*; do
	echo "${filename}:"
	./ip-adressen < $filename
done
