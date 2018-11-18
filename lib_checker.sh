#!/bin/sh

# Colors
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[0;33m'
BLUE='\033[0;34m'
MAGENTA='\033[0;35m'
NC='\033[0m'

# Compilation variables
CC="gcc"
CFLAGS="-Wall -Werror -Wextra"
CPPFLAGS="-I."
LFLAGS="-L. -lft"
COMPILE="${CC} ${CFLAGS} ${CPPFLAGS}"

# Special values
INT_MIN=-2147483648
INT_MAX=2147483647

# Other variables
OUTDIR=tests_output

# Display usage
if [ $# -eq 0 ]; then
	printf "${RED}%s${NC}\n" "Error: missing argument"
	printf "${RED}%s${NC}\n" "Usage: ./lib_checker.sh [ function_name | all ]"
	exit -1;
fi

# Clear screen
clear

# Save parameters
ALL=0
TEST_FCT=""
VERB=0
if [ "$1" = "all" ]; then
	ALL=1
	printf "Running all tests...\n"
else
	TEST_FCT="$1"
	printf "Running tests for ${BLUE}${TEST_FCT}${NC}...\n"
fi
if [ "$#" -eq 2 ]; then
	if [ "$2" = "-v" ]; then
		printf "Verbose mode: outputs will be displayed...\n"
		VERB=1
	fi
fi

# Compilation
compile() {
echo "Compiling $1_test.c..."
${COMPILE} tests/"$1"_test.c -o out/"$1"_test ${LFLAGS} # lib flags after for ubuntu
if [ $? -eq 0 ]; then
	printf "${GREEN}$1_test.c compiled without errors...${NC}\n"
	RETVAL=0
else
	printf "${RED}$1_test.c could not compile (Error: $?)...${NC}\n"
	RETVAL=-1
fi
return "${RETVAL}"
}

# Print function and parameters
print_fct_with_params() {
shift
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

# Print only parameters
print_params() {
shift; shift # skip function and function_name
printf "("
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
print_error() {
if [ "$1" -eq 139 ]; then
	printf "${RED}%s${NC}\n" "Segfault (${ERRCODE})"
elif [ "$1" -eq 134 ]; then
	printf "${RED}%s${NC}\n" "Abort (${ERRCODE})"
elif [ "$1" -ne 0 ]; then
	printf "${YELLOW}%s${NC}\n" "Unknown error"
fi
}

# Execute function
run_test() {
FCT="$1" # save function name
FCT_V="$2" # save function type (libc or user)
print_params "$@" # print function parameters
shift # remove function name from the list of parameters
{
	./out/${FCT}_test "$@" # execute function with all parameters
	ERRCODE=$?
} 2> /dev/null # do not display errors on stderr
print_error ${ERRCODE}
}

# Compare outputs
compare_outputs() {
	printf "Comparing outputs...\n"
	diff ${OUTDIR}/output_$1_$1 ${OUTDIR}/output_$1_ft_$1 > ${OUTDIR}/diff_$1
	if [ -s ${OUTDIR}/diff_${TEST_FCT} ]; then 
		printf "${BLUE}${TEST_FCT}${NC}: ${RED}Failed: errors detected${NC}\n"
		cat ${OUTDIR}/diff_${TEST_FCT}
	else
		printf "${BLUE}${TEST_FCT}${NC}: ${GREEN}Success${NC}\n"
	fi
}

# Create output directory if non existant
[ ! -d ${OUTDIR} ] && mkdir ${OUTDIR}

########################
# FONCTIONS DE LA LIBC #
########################

# memset
if [ "${TEST_FCT}" = "memset" ] || [ "${ALL}" = "1" ]; then
	TEST_FCT="memset"
	RETVAL=0
	compile ${TEST_FCT}
	RETVAL=$?
	if [ ${RETVAL} -eq 0 ]; then # if file compiled without errors
		for fct in ${TEST_FCT} ft_${TEST_FCT}
		do
			printf "Starting tests for ${MAGENTA}$fct${NC}...\n"
			{
			run_test ${TEST_FCT} $fct null 97 0 # s = NULL, c = 97, len = 0
			run_test ${TEST_FCT} $fct null 97 10 # s = NULL, c = 97, len = 10
			run_test ${TEST_FCT} $fct null 97 -1 # s = NULL, c = 97, len = -1
			run_test ${TEST_FCT} $fct 0 97 0 # s = 0, c = 97, len = 0 (s_size = 0)
			run_test ${TEST_FCT} $fct 0 97 -1 # s = 0, c = 97, len = -1 (s_size = 0, len < 0)
			run_test ${TEST_FCT} $fct 0 97 5 # s = 0, c = 97, len = 5 (s_size = 0, len > s_size)
			run_test ${TEST_FCT} $fct 10 97 0 # s = 10, c = 97, len = 0
			run_test ${TEST_FCT} $fct 10 97 -1 # s = 10, c = 97, len = -1 (len < 0)
			run_test ${TEST_FCT} $fct 10 97 5 # s = 10, c = 97, len = 5 (len < s_size)
			run_test ${TEST_FCT} $fct 10 ${INT_MAX} 5 # s = 10, c = 2147483647, len = 5 (c = int max, len < s_size)
			run_test ${TEST_FCT} $fct 10 97 15 # s = 10, c = 97, len = 15 (len > s_size)
			run_test ${TEST_FCT} $fct 10 97 999 # s = 10, c = 97, len = 999 (len >> s_size)
			run_test ${TEST_FCT} $fct 10 97 999999 # s = 10, c = 97, len = 999999 (len >> s_size)
			run_test ${TEST_FCT} $fct 10 97 ${INT_MAX} # s = 10, c = 97, len = 2147483647 (len >> s_size)
			} > ${OUTDIR}/output_${TEST_FCT}_${fct}
			printf "All tests for ${MAGENTA}$fct${NC} saved in ${MAGENTA}${OUTDIR}/output_${TEST_FCT}_${fct}${NC}...\n"
			if [ ${VERB} -eq 1 ]; then
				printf "Printing ${MAGENTA}${OUTDIR}/output_${TEST_FCT}_${fct}${NC}...\n"
				cat ${OUTDIR}/output_${TEST_FCT}_${fct}
			fi
		done
		compare_outputs ${TEST_FCT}
	fi
fi

# bzero
if [ "${TEST_FCT}" = "bzero" ] || [ "${ALL}" = "1" ]; then
	TEST_FCT="bzero"
	RETVAL=0
	compile ${TEST_FCT}
	RETVAL=$?
	if [ ${RETVAL} -eq 0 ]; then # if file compiled without errors
		for fct in ${TEST_FCT} ft_${TEST_FCT}
		do
			printf "Starting tests for ${MAGENTA}$fct${NC}...\n"
			{
			run_test ${TEST_FCT} $fct 0 # s = NULL pointer, n = 0
			run_test ${TEST_FCT} $fct 5 # s = NULL pointer, n = 5
			run_test ${TEST_FCT} $fct 0 0 # s = 0 bytes string, n = 0
			run_test ${TEST_FCT} $fct 0 10 # s = 0 bytes string, n = 10
			run_test ${TEST_FCT} $fct 10 10 # s = 10 bytes string, n = 10
			run_test ${TEST_FCT} $fct 10 -1 # s = 10 bytes string, n = -1
			run_test ${TEST_FCT} $fct 10 6 # s = 10 bytes string, n = 6
			run_test ${TEST_FCT} $fct 10 100 # s = 10 bytes string, n = 100
			run_test ${TEST_FCT} $fct 10 99999 # s = 10 bytes string, n = 99999
			run_test ${TEST_FCT} $fct 10 999999 # s = 10 bytes string, n = 999999
			run_test ${TEST_FCT} $fct 10 1000000 # s = 10 bytes string, n = 1000000
			run_test ${TEST_FCT} $fct 10 1000000 # s = 10 bytes string, n = 1000000
			run_test ${TEST_FCT} $fct 10 ${INT_MAX} # s = 10 bytes string, n = 2147483647
			} > ${OUTDIR}/output_${TEST_FCT}_${fct}
			printf "All tests for ${MAGENTA}$fct${NC} saved in ${MAGENTA}output_${TEST_FCT}_${fct}${NC}...\n"
			if [ ${VERB} -eq 1 ]; then
				cat ${OUTDIR}/output_${TEST_FCT}_${fct}
			fi
		done
		compare_outputs ${TEST_FCT}
	fi
fi

# memcpy
if [ "${TEST_FCT}" = "memcpy" ] || [ "${ALL}" = "1" ]; then
	TEST_FCT="memcpy"
	RETVAL=0
	compile ${TEST_FCT}
	RETVAL=$?
	if [ ${RETVAL} -eq 0 ]; then # if file compiled without errors
		for fct in ${TEST_FCT} ft_${TEST_FCT}
		do
			printf "Starting tests for ${MAGENTA}$fct${NC}...\n"
			{
			run_test ${TEST_FCT} $fct null "String containing char" 0 #dst = NULL, src = char string (22), n = 0
			run_test ${TEST_FCT} $fct null "String containing char" -1 #dst = NULL, src = char string (22), n = -1
			run_test ${TEST_FCT} $fct null "String containing char" 5 #dst = NULL, src = char string (22), n = 5
			run_test ${TEST_FCT} $fct null null 0 #dst = NULL, src = NULL, n = 0
			run_test ${TEST_FCT} $fct null null -1 #dst = NULL, src = NULL, n = -1
			run_test ${TEST_FCT} $fct null null 10 #dst = NULL, src = NULL, n = 10
			run_test ${TEST_FCT} $fct 30 null 0 #dst = char string (30), src = NULL, n = 0
			run_test ${TEST_FCT} $fct 30 null -1 #dst = char string (30), src = NULL, n = -1
			run_test ${TEST_FCT} $fct 30 null 10 #dst = char string (30), src = NULL, n = 10
			run_test ${TEST_FCT} $fct 30 "String containing char" 0 #dst = char string (30), src = char string (22), n = 0
			run_test ${TEST_FCT} $fct 30 "String containing char" -1 #dst = char string (30), src = char string (22), n = -1
			run_test ${TEST_FCT} $fct 30 "String containing char" 10 #dst = char string (30), src = char string (22), n = 10
			run_test ${TEST_FCT} $fct 30 "String containing char" 100 #dst = char string (30), src = char string (22), n = 100 (n > src_len)
			run_test ${TEST_FCT} $fct 30 "String containing char" 999999 #dst = char string (30), src = char string (22), n = 999999 (n > src_len)
			run_test ${TEST_FCT} $fct 10 "String containing char" 5 #dst = char string (10), src = char string (22), n = 5
			run_test ${TEST_FCT} $fct 10 "String containing char" 20 #dst = char string (10), src = char string (22), n = 20
			run_test ${TEST_FCT} $fct 10 "String containing char" 150 #dst = char string (10), src = char string (22), n = 150
			run_test ${TEST_FCT} $fct 10 "String containing char" ${INT_MAX} #dst = char string (10), src = char string (22), n = 2147483647
			} > ${OUTDIR}/output_${TEST_FCT}_${fct}
			printf "All tests for ${MAGENTA}$fct${NC} saved in ${MAGENTA}${OUTDIR}/output_${TEST_FCT}_${fct}${NC}...\n"
			if [ ${VERB} -eq 1 ]; then
				printf "Printing ${MAGENTA}${OUTDIR}/output_${TEST_FCT}_${fct}${NC}...\n"
				cat ${OUTDIR}/output_${TEST_FCT}_${fct}
			fi
		done
		compare_outputs ${TEST_FCT}
	fi
fi

