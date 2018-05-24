#!/bin/bash
# Usage: run tests
FILES=../tests/*.gr8
FILESASM=../tests/*.asm
FILESO=*.o
FILESEXE=../tests/exe/*
FILESCMO=../tests/expected
#shopt -s nullglob
echo
echo "----------------------------------------------------------------------------"
echo "                                 GENERATE ASSEMBLY" 
echo "----------------------------------------------------------------------------"
echo
for f in $FILES
do
	echo "- $(basename $f): " 
	./gr8 --target asm $f
done
echo
echo "----------------------------------------------------------------------------"
echo "                                 GENERATE .o" 
echo "----------------------------------------------------------------------------"
echo
for f1 in $FILESASM
do
	yasm -felf32 $f1
done
echo
echo "----------------------------------------------------------------------------"
echo "                                 GENERATE EXE"
echo "----------------------------------------------------------------------------"
echo
for f2 in $FILESO
do
	ld -melf_i386 -o ../tests/exe/$(basename $f2 .o) $f2 -lrts
done
echo
echo "----------------------------------------------------------------------------"
echo "                                 RUN PROGRAMS"
echo "----------------------------------------------------------------------------"
echo
for f3 in $FILESEXE
do
	$f3 > ../tests/expected/$(basename $f3).cout
done
echo
echo "----------------------------------------------------------------------------"
echo "                                 COMPARE RESULTS"
echo "----------------------------------------------------------------------------"
echo
for f4 in $FILESEXE
do
	echo "-> TEST $f4"
	diff --ignore-all-space --ignore-blank-lines --strip-trailing-cr ../tests/expected/$(basename $f4).cout ../tests/expected/$(basename $f4).out
done
rm *.o
