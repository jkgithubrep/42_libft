#!/bin/sh
# Display usage
if [[ $# -eq 0 ]]; then
	printf "%s\n" "Error: missing argument"
	printf "%s\n" "Usage: ./launcher.sh function_name"
fi

# Variables
CFLAGS="-Wall -Werror -Wextra"

# memset
if [ "$1" = "memset" ]; then
	TEST_FCT="memset"
	gcc -Wall -Werror -Wextra  -I. -L. -lft tests/base_memset_test.c -o out/base_memset_test
	function base_test_memset {
		{
		./out/base_memset_test $2 $3 $4
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
			for char in 97
			do
				for len in -2 150
				do
					base_test_memset $fct $b $char $len >> $fct\_errors.txt
				done
			done
		done
	done
	cat ${TEST_FCT}_errors.txt
fi

if [ "$1" = "memset2" ]; then
	gcc -Wall -Werror -Wextra  -I. -L. -lft tests/base_memset_test.c -o out/base_memset_test
	./out/base_memset_test
fi
