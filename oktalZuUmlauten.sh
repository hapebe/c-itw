#!/bin/bash
if [ -z $1 ] ; then
	echo "Usage: $0 <file name> in which to replace octal escape sequences with their corresponding Umlaut"
fi
sed -i 's/\\204/ä/g' $1
sed -i 's/\\224/ö/g' $1
sed -i 's/\\201/ü/g' $1
sed -i 's/\\216/Ä/g' $1
sed -i 's/\\231/Ö/g' $1
sed -i 's/\\232/Ü/g' $1
sed -i 's/\\341/ß/g' $1
