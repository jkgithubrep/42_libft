#!/bin/sh
# Display usage
if [[ $# -eq 0 ]]; then
	printf "%s\n" "Error: missing argument"
	printf "%s\n" "Usage: ./launcher.sh function_name | all"
fi

# Colors
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[0;33m'
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
	echo "All tests will be executed..."
else
	TEST_FCT="$1"
	echo "Tests for ${TEST_FCT} will be executed..."
fi

# Compilation
function compile {
echo "Compiling $1_test.c..."
${COMPILE} tests/"$1"_test.c -o out/"$1"_test
if [ $? -eq 0 ]; then
	echo "${GREEN}$1_test.c compiled without errors...${NC}"
	RETVAL=0
else
	echo "${RED}$1_test.c could not compile (Error: $?)...${NC}"
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
	printf "${GREEN}%s\n${NC}" "No error (0)" 
elif [ "$1" -eq 139 ]; then
	printf "${RED}%s\n${NC}" "Segfault (${ERRCODE})"
elif [ "$1" -eq 134 ]; then
	printf "${RED}%s\n${NC}" "Abort (${ERRCODE})"
else
	printf "${YELLOW}s\n${NC}" "Unknown error"
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
	} 2> /dev/null
	print_error ${ERRCODE}
fi
}

# bzero
if [ ${TEST_FCT} = "bzero" ] || [ ${ALL} -eq 1 ]; then
	#run_test ${TEST_FCT} 2 10
	compile ${TEST_FCT}
fi
