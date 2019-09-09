#!/bin/bash

root=$PWD

cd $root/ALattice
HFILES=`find . -type f -name '*.h' -not -path '*/old/*'`
CCFILES=`find . -name '*.cc' -not -path '*/old/*'`
echo HFILES=$HFILES > Make.inc
echo "# ================================" >> Make.inc
echo CCFILES=$CCFILES >> Make.inc


cd $root/tests
echo > Make.inc
TESTS=`ls *.cc`
TESTLIST=`echo ${TESTS} | sed s/.cc//g `
echo bin_PROGRAMS = ${TESTLIST} > Make.inc
echo >> Make.inc
for f in $TESTS; do
  BNAME=${f%.cc}
  echo ${BNAME}_SOURCES=$f  >> Make.inc
  echo ${BNAME}_LDADD=-lALattice >> Make.inc
  echo >> Make.inc
done
cd ..

cd $root
autoreconf
