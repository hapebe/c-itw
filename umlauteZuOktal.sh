#!/bin/bash
if [ -z $1 ] ; then
	echo "Usage: $0 <file name> in which to replace umlaute with their C octal escape sequence"
fi
sed -i 's/ä/\\204/g' $1
sed -i 's/ö/\\224/g' $1
sed -i 's/ü/\\201/g' $1
sed -i 's/Ä/\\216/g' $1
sed -i 's/Ö/\\231/g' $1
sed -i 's/Ü/\\232/g' $1
sed -i 's/ß/\\341/g' $1
