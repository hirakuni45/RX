#!/bin/bash
CMDNAME=`basename $0`
if [[ $1 = "-help" ]]; then
    echo "Usage: $CMDNAME options [clean]"
    echo "    -debug      debug build, 'OPTIMIZE=-O0'"
    echo ""
    exit
fi

# analize options
MAKE_OPTION=""
BUILD="release"
if [[ $1 = "-debug" ]]; then
    MAKE_OPTION="-e"
    export BUILD="debug"
    shift
fi

RED=`tput setaf 1`
GREEN=`tput setaf 2`
PINK=`tput setaf 5`
LIGHTBLUE=`tput setaf 6`
YELLO=`tput setaf 3`
NOCOLOR=`tput sgr0`

# make clean func
make_clean()
{
	cd "$2"
	echo "${GREEN}Clean project (${BUILD}): " $1 $2 "${NOCOLOR}"
	make ${MAKE_OPTION} clean >& /dev/null
	if [ $? -ne 0 ]; then
		echo "${RED}Clean Error: " $1 $2 "${NOCOLOR}"
		echo ""
		exit 1
	fi
	cd ..
}

# make clean
if [[ $1 = "clean" ]]; then
	for file in `ls -d *`;
	do
	    if [ ${file} = "legacy" ]; then
		echo "${YELLO}Legacy project: pass..." "${NOCOLOR}"
	    elif [ -e "${file}/Makefile" ]; then
		make_clean "" "${file}"
	    elif [ -d "${file}" ]; then
		cd "${file}"
		for proj in `ls -d *`;
		    do
			if [ -e "${proj}/Makefile" ]; then
			    make_clean "${file}" "${proj}"
			fi
		    done
			cd ..
	     fi
	done
	exit
fi

# make_main func
make_main()
{
	echo "${PINK}Start project (${BUILD}): " $1 $2 "${NOCOLOR}"
	cd $2
    make ${MAKE_OPTION} > /dev/null
    if [ $? -ne 0 ]; then
        echo "${RED}Compile error: " $1 $2 "${NOCOLOR}"
		echo ""
		exit 1
    fi
    cd ..
	echo "${LIGHTBLUE}Build project: " $1 $2 "${NOCOLOR}"	
}

# make
# first build drw2d library
for file in `ls -d RX600/drw2d`;
do
    if [ -e "${file}/Makefile" ]; then
		make_main "" ${file}
		cd ..
    fi
done
for file in `ls -d *`;
do
    	if [ ${file} = "legacy" ]; then
	    echo "${YELLO}Legacy project: pass..." "${NOCOLOR}"
	elif [ -e "${file}/Makefile" ]; then
		make_main "" ${file}
	elif [ -d "${file}" ]; then
		cd "${file}"
		for proj in `ls -d *`;
		do
			if [ -e "${proj}/Makefile" ]; then
				make_main "${file}" "${proj}"
			fi
		done
		cd ..
	fi
done
