#!/bin/sh
# echo on
make build
make run
echo $?
if [ "echo $?" != 0]
then
  echo "Error"
  exit 0
else
  echo "Compiled it✅"
fi
