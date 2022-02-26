#!/bin/sh
# echo on
echo "Enter [ 1 ] debug mode"
echo "Enter [ 2 ] normal mode"
echo "Enter [ 0 ] help mode"
read option

make build

if [ $option -eq 0 ] ; then
  make help
elif [ $option -eq 1 ] ; then
  make runDebug
elif [ $option -eq 2 ] ; then
  make run
else
  echo -e "\n$(tput setaf 3)$(tput bold)INV Option$(tput init)"
  exit 1
fi
ret=`echo $?`
if [ $ret -eq 0 ]
then
  echo -e "\n$(tput setaf 2)$(tput bold)Successful Compilation$(tput init)"
else
  echo -e "\n$(tput setaf 1)$(tput bold)ERROR$(tput init)"
  exit 0
fi
make clean
