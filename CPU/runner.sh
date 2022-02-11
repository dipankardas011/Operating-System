#!/bin/sh
# echo on
make build
make run
ret=`echo $?`
if [ $ret -eq 0 ]
then
  echo "Compiled it✅ "
else
  echo "Error❌ "
  exit 0
fi
