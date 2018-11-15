#!/bin/sh
# Display usage
if [[ $# -eq 0 ]]; then
	printf "%s\n" "Error: missing argument"
	printf "%s\n" "Usage: ./launcher.sh function_name | all"
fi

# Colors
RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m'

# Variables
CC="gcc"
CFLAGS="-Wall -Werror -Wextra"
CPPFLAGS="-I."
LFLAGS="-L. -lft"
COMPILE="${CC} ${CFLAGS} ${CPPFLAGS} ${LFLAGS}"

# Save parameters
ALL=0
if [ "$1" = "all" ]; then
	ALL=1
	echo "All tests will be executed."
else
	TEST_FCT="$1"
	echo "Tests for ${TEST_FCT} will be executed."
fi

# Compilation
function compile {
echo "Compiling $1_test.c..."
${COMPILE} tests/"$1"_test.c -o out/"$1"_test
if [ $? -eq 0 ]; then
	echo "$1_test.c compiled without errors."
	RETVAL=0
else
	echo "$1_test.c could not compile (Error: $?)"
	RETVAL=-1
fi
return "${RETVAL}"
}

# Print function and parameters
function	print_fct_with_params {
printf "%s(" "$1"
shift
while [ "$#" -gt 0 ]
do
	printf "%s" "$1"
	[ "$#" -gt 1 ] \
		&& printf ", "
	shift
done
printf "): "
}

# Error output
function print_error {
if [ "$1" -eq 0 ]; then
	printf "%s\n" "No error (0)" 
elif [ "$1" -eq 139 ]; then
	printf "%s\n" "Segfault (${ERRCODE})"
elif [ "$1" -eq 134 ]; then
	printf "%s\n" "Abort (${ERRCODE})"
else
	printf "s\n" "Unknown error"
fi
}

# Execute function
function run_test {
FCT=$1 # save function name
compile ${FCT}
RETVAL=$?
if [ ${RETVAL} -eq 0 ]; then
	print_fct_with_params $@
	shift # remove function name from the list of parameters
	{
		./out/${FCT}_test $@ # execute function with all parameters
		ERRCODE=$?
	} #2> /dev/null
	print_error ${ERRCODE}
fi
}

# test
if [ ${TEST_FCT} = "test" ] || [ ${ALL} -eq 1 ]; then
	compile memset
fi

# bzero
if [ ${TEST_FCT} = "bzero" ] || [ ${ALL} -eq 1 ]; then
	run_test ${TEST_FCT} 0 2
fi

# memset
if [ ${TEST_FCT} = "memset" ]; then
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
