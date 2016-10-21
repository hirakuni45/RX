#!/bin/bash
CMDNAME=`basename $0`
if [[ $1 = "help" ]]; then
  echo "Usage: $CMDNAME [clean]"
  echo ""
  exit
fi

RED=`tput setaf 1`
GREEN=`tput setaf 2`
PINK=`tput setaf 5`
LIGHTBLUE=`tput setaf 6`
NOCOLOR=`tput sgr0`

# make clean
if [[ $1 = "clean" ]]; then
  for file in `ls -d *`
  do
    if [ -e "${file}/Makefile" ]; then
      cd "${file}"
      echo "${GREEN}Clean project: " ${file} "${NOCOLOR}"
      make clean >& /dev/null
      if [ $? -ne 0 ]; then
          echo "${RED}Error: " ${file} "${NOCOLOR}"
          echo ""
          break;
      fi
	  cd ..
    fi
  done
fi

# make
for file in `ls -d *`
do
  if [ -e "${file}/Makefile" ]; then
	echo "${PINK}Start project: " ${file} "${NOCOLOR}"
    cd "${file}"
    make > /dev/null
    if [ $? -ne 0 ]; then
        echo "${RED}Compile error: " ${file} "${NOCOLOR}"
		echo ""
        break;
    fi
    cd ..
	echo "${LIGHTBLUE}Build project: " ${file} "${NOCOLOR}"
  fi
done
