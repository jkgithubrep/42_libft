#!/bin/sh
# Display usage
if [[ $# -eq 0 ]]; then
	printf "%s\n" "Error: missing argument"
	printf "%s\n" "Usage: ./launcher.sh function_name"
fi

# Variables
CC="gcc"
CFLAGS="-Wall -Werror -Wextra"
CPPFLAGS="-I."
LFLAGS="-L. -lft"
COMPILE = ${CC} ${CFLAGS} ${CPPFLAGS}

# Get function name
TEST_FCT="$1"

# Compilation
${COMPILE} tests/${TEST_FCT}_test.c -o out/${TEST_FCT}_test

# Print function and parameters
function	print_params {

}

# Error output
function error_output {
	if [ ${ERRCODE} -eq 0 ]; then
		 printf "%s(%s, %d, %d): %s\n" $1 $2 $3 $4 "No error (0)" 
	elif [ ${ERRCODE} -eq 139 ]; then
		 printf "%s(%s, %d, %d): %s\n" $1 $2 $3 $4 "Segfault (${ERRCODE})"
	elif [ ${ERRCODE} -eq 134 ]; then
		 printf "%s(%s, %d, %d): %s\n" $1 $2 $3 $4 "Abort (${ERRCODE})"
	fi
}


# bzero
if [ ${TEST_FCT} = "bzero" ]; then
	
fi

# memset
if [ ${TEST_FCT} = "memset" ]; then
	${COMPILE} tests/${TEST_FCT}_test.c -o out/${TEST_FCT}_test
	function memset_test {
		{
		./out/${TEST_FCT}_test $2 $3 $4
		ERRCODE=$?
		} #2> /dev/null
		if [ ${ERRCODE} -eq 0 ]; then
			 printf "%s(%s, %d, %d): %s\n" $1 $2 $3 $4 "No error (0)" 
		elif [ ${ERRCODE} -eq 139 ]; then
			 printf "%s(%s, %d, %d): %s\n" $1 $2 $3 $4 "Segfault (${ERRCODE})"
		elif [ ${ERRCODE} -eq 134 ]; then
			 printf "%s(%s, %d, %d): %s\n" $1 $2 $3 $4 "Abort (${ERRCODE})"
		fi
	}
	for fct in ${TEST_FCT}
	do
		printf "" > $fct\_errors.txt
		for b in NULL unsigned_char[100] # test NULL pointer and byte string
		do
			for char in 0 97
			do
				for len in -2 150
				do
					base_test_memset $fct $b $char $len >> $fct\_output.txt
				done
			done
		done
	done
	cat ${TEST_FCT}_output.txt
fi
