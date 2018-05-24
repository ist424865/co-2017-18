#!/bin/bash
# Usage: run tests
FILES=../tests/*.xml
#shopt -s nullglob
for f in $FILES
do
	rm $f
done
