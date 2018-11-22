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
	printf "${RED}%s${NC}\n" "Usage: ./lib_checker.sh [ function_name | all ] [-v]"
	exit 1;
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
		printf "Verbose mode: outputs will be displayed\n"
		VERB=1
	fi
fi
printf "\n"

# Compilation
compile() {
printf "#########################\n"
printf "Compiling $1_test.c...\n"
${COMPILE} tests/"$1"_test.c -o out/"$1"_test ${LFLAGS} # lib flags after for ubuntu
if [ $? -eq 0 ]; then
	printf "${GREEN}$1_test.c compiled without errors${NC}\n"
	RETVAL=0
else
	printf "· ${TEST_FCT}: ${RED}FAILED [Compilation]${NC}\n" >> ${OUTDIR}/output_summary
	printf "${RED}$1_test.c could not compile (Error: $?)${NC}\n"
	RETVAL=1
fi
printf "\n"
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

# Print only parameters for other functions
print_params_other() {
shift # skip function
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

# Execute test libc
run_test_libc() {
FCT="$1" # save function name
FCT_V="$2" # save function type (libc or user)
print_params "$@" # print function parameters
shift # remove function name from the list of parameters
{
	./out/${FCT}_test "$@" # execute function with all parameters
	ERRCODE=$?
} 2> /dev/null # do not display errors on stderr
if [ ${ERRCODE} -eq 0 ]; then
	printf "\n"
else
	print_error ${ERRCODE}
fi
}

# Execute test other functions
run_test_other() {
FCT="$1" # save function name
print_params_other "$@" # print function parameters
shift # remove function name from the list of parameters
{
	./out/${FCT}_test "$@" # execute function with all parameters
	ERRCODE=$?
} 2> /dev/null # do not display errors on stderr
if [ ${ERRCODE} -eq 0 ]; then
	printf "\n"
else
	print_error ${ERRCODE}
fi
}

# Compare outputs
compare_outputs() {
	printf "Comparing outputs...\n"
	diff ${OUTDIR}/output_$1_$1 ${OUTDIR}/output_$1_ft_$1 > ${OUTDIR}/diff_$1
	if [ -s ${OUTDIR}/diff_${TEST_FCT} ]; then 
		printf "· ${TEST_FCT}: ${RED}FAILED${NC}\n" >> ${OUTDIR}/output_summary
		printf "${BLUE}${TEST_FCT}${NC}: ${RED}Failed: outputs differ${NC}\n"
		cat ${OUTDIR}/diff_${TEST_FCT}
	else
		printf "· ${TEST_FCT}: ${GREEN}OK${NC}\n" >> ${OUTDIR}/output_summary
		printf "${BLUE}${TEST_FCT}${NC}: ${GREEN}Success${NC}\n"
	fi
	printf "\n"
}

# Print mini ascii table
print_ascii_tbl(){
	cat ascii_table.txt
}

# Print output summary
print_summary(){
	printf "###########\n"
	printf "# SUMMARY #\n"
	printf "###########\n\n"
	cat ${OUTDIR}/output_summary
	printf "\n"
}

# Create output directory if non existant
[ ! -d ${OUTDIR} ] && mkdir ${OUTDIR}

# Erase output/output_summary
printf "" > ${OUTDIR}/output_summary

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
			run_test_libc ${TEST_FCT} $fct null 97 0 # s = NULL, c = 97, len = 0
			run_test_libc ${TEST_FCT} $fct null 97 10 # s = NULL, c = 97, len = 10
			run_test_libc ${TEST_FCT} $fct null 97 -1 # s = NULL, c = 97, len = -1
			run_test_libc ${TEST_FCT} $fct 0 97 0 # s = 0, c = 97, len = 0 (s_size = 0)
			run_test_libc ${TEST_FCT} $fct 0 97 0 # s = 0, c = 97, len = -1 (s_size = 0, len < 0)
			run_test_libc ${TEST_FCT} $fct 0 97 5 # s = 0, c = 97, len = 5 (s_size = 0, len > s_size)
			run_test_libc ${TEST_FCT} $fct 10 97 0 # s = 10, c = 97, len = 0
			run_test_libc ${TEST_FCT} $fct 10 97 -1 # s = 10, c = 97, len = -1 (len < 0)
			run_test_libc ${TEST_FCT} $fct 10 97 5 # s = 10, c = 97, len = 5 (len < s_size)
			run_test_libc ${TEST_FCT} $fct 10 ${INT_MAX} 5 # s = 10, c = 2147483647, len = 5 (c = int max, len < s_size)
			run_test_libc ${TEST_FCT} $fct 10 97 15 # s = 10, c = 97, len = 15 (len > s_size)
			run_test_libc ${TEST_FCT} $fct 10 97 999 # s = 10, c = 97, len = 999 (len >> s_size)
			run_test_libc ${TEST_FCT} $fct 10 97 999999 # s = 10, c = 97, len = 999999 (len >> s_size)
			run_test_libc ${TEST_FCT} $fct 10 97 ${INT_MAX} # s = 10, c = 97, len = 2147483647 (len >> s_size)
			} > ${OUTDIR}/output_${TEST_FCT}_${fct}
			printf "All tests for ${MAGENTA}$fct${NC} saved in ${MAGENTA}${OUTDIR}/output_${TEST_FCT}_${fct}${NC}\n"
			if [ ${VERB} -eq 1 ]; then
				printf "Printing ${MAGENTA}${OUTDIR}/output_${TEST_FCT}_${fct}${NC}...\n"
				cat ${OUTDIR}/output_${TEST_FCT}_${fct}
			fi
			printf "\n"
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
			run_test_libc ${TEST_FCT} $fct null 0 # s = NULL pointer, n = 0
			run_test_libc ${TEST_FCT} $fct null 5 # s = NULL pointer, n = 5
			run_test_libc ${TEST_FCT} $fct 0 0 # s = 0 bytes string, n = 0
			run_test_libc ${TEST_FCT} $fct 0 10 # s = 0 bytes string, n = 10
			run_test_libc ${TEST_FCT} $fct 10 10 # s = 10 bytes string, n = 10
			run_test_libc ${TEST_FCT} $fct 10 -1 # s = 10 bytes string, n = -1
			run_test_libc ${TEST_FCT} $fct 10 6 # s = 10 bytes string, n = 6
			run_test_libc ${TEST_FCT} $fct 10 100 # s = 10 bytes string, n = 100
			run_test_libc ${TEST_FCT} $fct 10 99999 # s = 10 bytes string, n = 99999
			run_test_libc ${TEST_FCT} $fct 10 999999 # s = 10 bytes string, n = 999999
			run_test_libc ${TEST_FCT} $fct 10 1000000 # s = 10 bytes string, n = 1000000
			run_test_libc ${TEST_FCT} $fct 10 1000000 # s = 10 bytes string, n = 1000000
			run_test_libc ${TEST_FCT} $fct 10 ${INT_MAX} # s = 10 bytes string, n = 2147483647
			} > ${OUTDIR}/output_${TEST_FCT}_${fct}
			printf "All tests for ${MAGENTA}$fct${NC} saved in ${MAGENTA}output_${TEST_FCT}_${fct}${NC}\n"
			if [ ${VERB} -eq 1 ]; then
				cat ${OUTDIR}/output_${TEST_FCT}_${fct}
			fi
			printf "\n"
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
			run_test_libc ${TEST_FCT} $fct null "String containing char" 0 #dst = NULL, src = char string (22), n = 0
			run_test_libc ${TEST_FCT} $fct null "String containing char" -1 #dst = NULL, src = char string (22), n = -1
			run_test_libc ${TEST_FCT} $fct null "String containing char" 5 #dst = NULL, src = char string (22), n = 5
			run_test_libc ${TEST_FCT} $fct null null 0 #dst = NULL, src = NULL, n = 0
			run_test_libc ${TEST_FCT} $fct null null -1 #dst = NULL, src = NULL, n = -1
			run_test_libc ${TEST_FCT} $fct null null 10 #dst = NULL, src = NULL, n = 10
			run_test_libc ${TEST_FCT} $fct 30 null 0 #dst = char string (30), src = NULL, n = 0
			run_test_libc ${TEST_FCT} $fct 30 null -1 #dst = char string (30), src = NULL, n = -1
			run_test_libc ${TEST_FCT} $fct 30 null 10 #dst = char string (30), src = NULL, n = 10
			run_test_libc ${TEST_FCT} $fct 30 2 10 #dst = char string (30), src = dst + 2, n = 10
			run_test_libc ${TEST_FCT} $fct 30 "String containing char" 0 #dst = char string (30), src = char string (22), n = 0
			run_test_libc ${TEST_FCT} $fct 30 "String containing char" -1 #dst = char string (30), src = char string (22), n = -1
			run_test_libc ${TEST_FCT} $fct 30 "String containing char" 10 #dst = char string (30), src = char string (22), n = 10
			run_test_libc ${TEST_FCT} $fct 30 "String containing char" 100 #dst = char string (30), src = char string (22), n = 100 (n > src_len)
			run_test_libc ${TEST_FCT} $fct 30 "String containing char" 999999 #dst = char string (30), src = char string (22), n = 999999 (n > src_len)
			run_test_libc ${TEST_FCT} $fct 10 "String containing char" 5 #dst = char string (10), src = char string (22), n = 5
			run_test_libc ${TEST_FCT} $fct 10 "String containing char" 20 #dst = char string (10), src = char string (22), n = 20
			run_test_libc ${TEST_FCT} $fct 10 "String containing char" 150 #dst = char string (10), src = char string (22), n = 150
			run_test_libc ${TEST_FCT} $fct 10 "String containing char" ${INT_MAX} #dst = char string (10), src = char string (22), n = 2147483647
			} > ${OUTDIR}/output_${TEST_FCT}_${fct}
			printf "All tests for ${MAGENTA}$fct${NC} saved in ${MAGENTA}${OUTDIR}/output_${TEST_FCT}_${fct}${NC}\n"
			if [ ${VERB} -eq 1 ]; then
				printf "Printing ${MAGENTA}${OUTDIR}/output_${TEST_FCT}_${fct}${NC}...\n"
				cat ${OUTDIR}/output_${TEST_FCT}_${fct}
			fi
			printf "\n"
		done
		compare_outputs ${TEST_FCT}
	fi
fi

# memccpy
if [ "${TEST_FCT}" = "memccpy" ] || [ "${ALL}" = "1" ]; then
	TEST_FCT="memccpy"
	RETVAL=0
	compile ${TEST_FCT}
	RETVAL=$?
	if [ ${RETVAL} -eq 0 ]; then # if file compiled without errors
		for fct in ${TEST_FCT} ft_${TEST_FCT}
		do
			printf "Starting tests for ${MAGENTA}$fct${NC}...\n"
			{
				run_test_libc ${TEST_FCT} $fct null null 'a' 0 #dst = null, src = null, c = 'a' (97), n = 0
				run_test_libc ${TEST_FCT} $fct null null ${INT_MAX} 0 #dst = null, src = null, c = 2147483647, n = 0
				run_test_libc ${TEST_FCT} $fct null null 'a' -1 #dst = null, src = null, c = 'a' (97), n = -1
				run_test_libc ${TEST_FCT} $fct null null 'a' 10 #dst = null, src = null, c = 'a' (97), n = 10
				run_test_libc ${TEST_FCT} $fct null "String containing char" 'a' 0 #dst = null, src = char string (22), c = 'a' (97), n = 0
				run_test_libc ${TEST_FCT} $fct null "String containing char" 'a' -1 #dst = null, src = char string (22), c = 'a' (97), n = -1
				run_test_libc ${TEST_FCT} $fct null "String containing char" 'a' 10 #dst = null, src = char string (22), c = 'a' (97), n = 10
				run_test_libc ${TEST_FCT} $fct 30 null 'a' 0 #dst = char string (30), src = null, c = 'a' (97), n = 0
				run_test_libc ${TEST_FCT} $fct 30 null 'a' -1 #dst = char string (30), src = null, c = 'a' (97), n = -1
				run_test_libc ${TEST_FCT} $fct 30 null 'a' 10 #dst = char string (30), src = null, c = 'a' (97), n = 10
				run_test_libc ${TEST_FCT} $fct 30 "String containing char" 'a' 0 #dst = char string (30), src = char string (22), c = 'a' (97), n = 0
				run_test_libc ${TEST_FCT} $fct 30 "String containing char" 'a' -1 #dst = char string (30), src = char string (22), c = 'a' (97), n = -1 (n < 0)
				run_test_libc ${TEST_FCT} $fct 30 "String containing char" 'a' 22 #dst = char string (30), src = char string (22), c = 'a' (97), n = 22 (char in string)
				run_test_libc ${TEST_FCT} $fct 30 "String containing char" 'x' 22 #dst = char string (30), src = char string (22), c = 'x' (97), n = 22 (char not in string)
				run_test_libc ${TEST_FCT} $fct 30 "String containing char" 'a' 7 #dst = char string (30), src = char string (22), c = 'a' (97), n = 7 (char in string but n before)
				run_test_libc ${TEST_FCT} $fct 30 "String containing char" 'x' 50 #dst = char string (30), src = char string (22), c = 'a' (97), n = 50 (char not in string and n > src_len)
				run_test_libc ${TEST_FCT} $fct 30 "String containing char" 'x' 9999 #dst = char string (30), src = char string (22), c = 'a' (97), n = 9999 (char not in string and n > src_len)
				run_test_libc ${TEST_FCT} $fct 30 "String containing char" 'x' 1000000 #dst = char string (30), src = char string (22), c = 'a' (97), n = 1000000 (char not in string and n >> src_len)
			} > ${OUTDIR}/output_${TEST_FCT}_${fct}
			printf "All tests for ${MAGENTA}$fct${NC} saved in ${MAGENTA}${OUTDIR}/output_${TEST_FCT}_${fct}${NC}\n"
			if [ ${VERB} -eq 1 ]; then
				printf "Printing ${MAGENTA}${OUTDIR}/output_${TEST_FCT}_${fct}${NC}...\n"
				cat ${OUTDIR}/output_${TEST_FCT}_${fct}
			fi
			printf "\n"
		done
		compare_outputs ${TEST_FCT}
	fi
fi

# memmove
if [ "${TEST_FCT}" = "memmove" ] || [ "${ALL}" = "1" ]; then
	TEST_FCT="memmove"
	RETVAL=0
	compile ${TEST_FCT}
	RETVAL=$?
	if [ ${RETVAL} -eq 0 ]; then # if file compiled without errors
		for fct in ${TEST_FCT} ft_${TEST_FCT}
		do
			printf "Starting tests for ${MAGENTA}$fct${NC}...\n"
			{
				run_test_libc ${TEST_FCT} $fct null null 0 #dst = null, src = null, len = 0
				run_test_libc ${TEST_FCT} $fct null null -1 #dst = null, src = null, len = -1
				run_test_libc ${TEST_FCT} $fct null null 10 #dst = null, src = null, len = 10
				run_test_libc ${TEST_FCT} $fct null "String containing char" 0 #dst = null, src = char string (22), len = 0
				run_test_libc ${TEST_FCT} $fct null "String containing char" -1 #dst = null, src = char string (22), len = -1
				run_test_libc ${TEST_FCT} $fct null "String containing char" 10 #dst = null, src = char string (22), len = 10
				run_test_libc ${TEST_FCT} $fct 30 null 0 #dst = char string (30), src = null, len = 0
				run_test_libc ${TEST_FCT} $fct 30 null -1 #dst = char string (30), src = null, len = -1
				run_test_libc ${TEST_FCT} $fct 30 null 10 #dst = char string (30), src = null, len = 10
				run_test_libc ${TEST_FCT} $fct 30 "String containing char" 0 #dst = char string (30), src = char string (22), len = 0
				run_test_libc ${TEST_FCT} $fct 30 "String containing char" -1 #dst = char string (30), src = char string (22), len = -1 (len < 0)
				run_test_libc ${TEST_FCT} $fct 30 "String containing char" 10 #dst = char string (30), src = char string (22), len = 10 (len < src_size)
				run_test_libc ${TEST_FCT} $fct 30 "String containing char" 22 #dst = char string (30), src = char string (22), len = 23 (len = src_size)
				run_test_libc ${TEST_FCT} $fct 30 "String containing char" 26 #dst = char string (30), src = char string (22), len = 26 (src_size < len < dst_size)
				run_test_libc ${TEST_FCT} $fct 30 "String containing char" 100 #dst = char string (30), src = char string (22), len = 100 (len > dst_size)
				run_test_libc ${TEST_FCT} $fct 30 "String containing char" 9999 #dst = char string (30), src = char string (22), len = 9999 (len >> dst_size)
				run_test_libc ${TEST_FCT} $fct 30 "String containing char" 1000000 #dst = char string (30), src = char string (22), len = 1000000 (len >>> src_len)
				run_test_libc ${TEST_FCT} $fct 10 "String containing char" 22 #dst = char string (10), src = char string (22), len = 23 (dst_size < src_size)
				run_test_libc ${TEST_FCT} $fct 10 "String containing char" 26 #dst = char string (10), src = char string (22), len = 26 (dst_size < src_size)
			} > ${OUTDIR}/output_${TEST_FCT}_${fct}
			printf "All tests for ${MAGENTA}$fct${NC} saved in ${MAGENTA}${OUTDIR}/output_${TEST_FCT}_${fct}${NC}\n"
			if [ ${VERB} -eq 1 ]; then
				printf "Printing ${MAGENTA}${OUTDIR}/output_${TEST_FCT}_${fct}${NC}...\n"
				cat ${OUTDIR}/output_${TEST_FCT}_${fct}
			fi
			printf "\n"
		done
		compare_outputs ${TEST_FCT}
	fi
fi

# memchr
if [ "${TEST_FCT}" = "memchr" ] || [ "${ALL}" = "1" ]; then
	TEST_FCT="memchr"
	RETVAL=0
	compile ${TEST_FCT}
	RETVAL=$?
	if [ ${RETVAL} -eq 0 ]; then # if file compiled without errors
		for fct in ${TEST_FCT} ft_${TEST_FCT}
		do
			printf "Starting tests for ${MAGENTA}$fct${NC}...\n"
			{
				run_test_libc ${TEST_FCT} $fct null 65 0
				run_test_libc ${TEST_FCT} $fct null 65 2
				run_test_libc ${TEST_FCT} $fct null 65 -1
				run_test_libc ${TEST_FCT} $fct "" 65 0
				run_test_libc ${TEST_FCT} $fct "" 65 -1
				run_test_libc ${TEST_FCT} $fct "" 65 5
				run_test_libc ${TEST_FCT} $fct "ABC" 0 1
				run_test_libc ${TEST_FCT} $fct "ABC" 0 3
				run_test_libc ${TEST_FCT} $fct "ABC" 0 5
				run_test_libc ${TEST_FCT} $fct "ABC" 65 0
				run_test_libc ${TEST_FCT} $fct "ABC" 65 -1
				run_test_libc ${TEST_FCT} $fct "ABC" 65 3
				run_test_libc ${TEST_FCT} $fct "ABC" 'A' 3
				run_test_libc ${TEST_FCT} $fct "ABC" 65 5
				run_test_libc ${TEST_FCT} $fct "ABC" 'D' 3
				run_test_libc ${TEST_FCT} $fct "ABC" 'D' 10
				run_test_libc ${TEST_FCT} $fct "ABC" 68 10
				run_test_libc ${TEST_FCT} $fct "ABC" 70 3
				run_test_libc ${TEST_FCT} $fct "ABC" ${INT_MIN} 3
				run_test_libc ${TEST_FCT} $fct "ABC" ${INT_MAX} 3
			} > ${OUTDIR}/output_${TEST_FCT}_${fct}
			printf "All tests for ${MAGENTA}$fct${NC} saved in ${MAGENTA}${OUTDIR}/output_${TEST_FCT}_${fct}${NC}\n"
			if [ ${VERB} -eq 1 ]; then
				printf "Printing ${MAGENTA}${OUTDIR}/output_${TEST_FCT}_${fct}${NC}...\n"
				cat ${OUTDIR}/output_${TEST_FCT}_${fct}
			fi
			printf "\n"
		done
		compare_outputs ${TEST_FCT}
	fi
fi

# memcmp
if [ "${TEST_FCT}" = "memcmp" ] || [ "${ALL}" = "1" ]; then
	TEST_FCT="memcmp"
	RETVAL=0
	compile ${TEST_FCT}
	RETVAL=$?
	if [ ${RETVAL} -eq 0 ]; then # if file compiled without errors
		for fct in ${TEST_FCT} ft_${TEST_FCT}
		do
			printf "Starting tests for ${MAGENTA}$fct${NC}...\n"
			{
				run_test_libc ${TEST_FCT} $fct null null 0
				run_test_libc ${TEST_FCT} $fct null null -1
				run_test_libc ${TEST_FCT} $fct null null 1
				run_test_libc ${TEST_FCT} $fct null null 5
				run_test_libc ${TEST_FCT} $fct null "" 0
				run_test_libc ${TEST_FCT} $fct null "" -1
				run_test_libc ${TEST_FCT} $fct null "" 1
				run_test_libc ${TEST_FCT} $fct null "" 2
				run_test_libc ${TEST_FCT} $fct null "" 3
				run_test_libc ${TEST_FCT} $fct null "abcd" 0
				run_test_libc ${TEST_FCT} $fct null "abcd" 1
				run_test_libc ${TEST_FCT} $fct null "abcd" 2
				run_test_libc ${TEST_FCT} $fct null "abcd" 5
				run_test_libc ${TEST_FCT} $fct "abcd" null 0
				run_test_libc ${TEST_FCT} $fct "abcd" null -1
				run_test_libc ${TEST_FCT} $fct "abcd" null 2
				run_test_libc ${TEST_FCT} $fct "abcd" null 5
				run_test_libc ${TEST_FCT} $fct "" null 0
				run_test_libc ${TEST_FCT} $fct "" null 1
				run_test_libc ${TEST_FCT} $fct "" null 2
				run_test_libc ${TEST_FCT} $fct "" null 5
				run_test_libc ${TEST_FCT} $fct "" "" 0
				run_test_libc ${TEST_FCT} $fct "" "" 1
				run_test_libc ${TEST_FCT} $fct "" "" 2
				run_test_libc ${TEST_FCT} $fct "abcd" "a" 0
				run_test_libc ${TEST_FCT} $fct "abcd" "a" 1
				run_test_libc ${TEST_FCT} $fct "abcd" "a" 2
				run_test_libc ${TEST_FCT} $fct "abcd" "abc" 0
				run_test_libc ${TEST_FCT} $fct "abcd" "abc" 1
				run_test_libc ${TEST_FCT} $fct "abcd" "abc" 2
				run_test_libc ${TEST_FCT} $fct "abcd" "abcd" 0
				run_test_libc ${TEST_FCT} $fct "abcd" "abcd" 1
				run_test_libc ${TEST_FCT} $fct "abcd" "abcd" 2
				run_test_libc ${TEST_FCT} $fct "abcd" "abcd" 3
				run_test_libc ${TEST_FCT} $fct "abcd" "abcd" 4
				run_test_libc ${TEST_FCT} $fct "abcd" "abcd" 5
				run_test_libc ${TEST_FCT} $fct "abcd" "abcd" 10
				run_test_libc ${TEST_FCT} $fct "abcd" "abcde" 0
				run_test_libc ${TEST_FCT} $fct "abcd" "abcde" 1
				run_test_libc ${TEST_FCT} $fct "abcd" "abcde" 4
				run_test_libc ${TEST_FCT} $fct "abcd" "abcde" 5
				run_test_libc ${TEST_FCT} $fct "abcd" "abce" 0
				run_test_libc ${TEST_FCT} $fct "abcd" "abce" 1
				run_test_libc ${TEST_FCT} $fct "abcd" "abce" 4
				run_test_libc ${TEST_FCT} $fct "abcd" "bc" 0
				run_test_libc ${TEST_FCT} $fct "abcd" "bc" 2
				run_test_libc ${TEST_FCT} $fct "abcd" "bcd" 0
				run_test_libc ${TEST_FCT} $fct "abcd" "bcd" 2
				run_test_libc ${TEST_FCT} $fct "abc" "ABC" 0
				run_test_libc ${TEST_FCT} $fct "abc" "ABC" 3
			} > ${OUTDIR}/output_${TEST_FCT}_${fct}
			printf "All tests for ${MAGENTA}$fct${NC} saved in ${MAGENTA}${OUTDIR}/output_${TEST_FCT}_${fct}${NC}\n"
			if [ ${VERB} -eq 1 ]; then
				printf "Printing ${MAGENTA}${OUTDIR}/output_${TEST_FCT}_${fct}${NC}...\n"
				cat ${OUTDIR}/output_${TEST_FCT}_${fct}
			fi
			printf "\n"
		done
		compare_outputs ${TEST_FCT}
	fi
fi

# strlen
if [ "${TEST_FCT}" = "strlen" ] || [ "${ALL}" = "1" ]; then
	TEST_FCT="strlen"
	RETVAL=0
	compile ${TEST_FCT}
	RETVAL=$?
	if [ ${RETVAL} -eq 0 ]; then # if file compiled without errors
		for fct in ${TEST_FCT} ft_${TEST_FCT}
		do
			printf "Starting tests for ${MAGENTA}$fct${NC}...\n"
			{
				run_test_libc ${TEST_FCT} $fct null
				run_test_libc ${TEST_FCT} $fct ""
				run_test_libc ${TEST_FCT} $fct "This string contains 34 characters"
			} > ${OUTDIR}/output_${TEST_FCT}_${fct}
			printf "All tests for ${MAGENTA}$fct${NC} saved in ${MAGENTA}${OUTDIR}/output_${TEST_FCT}_${fct}${NC}\n"
			if [ ${VERB} -eq 1 ]; then
				printf "Printing ${MAGENTA}${OUTDIR}/output_${TEST_FCT}_${fct}${NC}...\n"
				cat ${OUTDIR}/output_${TEST_FCT}_${fct}
			fi
			printf "\n"
		done
		compare_outputs ${TEST_FCT}
	fi
fi

# strdup
if [ "${TEST_FCT}" = "strdup" ] || [ "${ALL}" = "1" ]; then
	TEST_FCT="strdup"
	RETVAL=0
	compile ${TEST_FCT}
	RETVAL=$?
	if [ ${RETVAL} -eq 0 ]; then # if file compiled without errors
		for fct in ${TEST_FCT} ft_${TEST_FCT}
		do
			printf "Starting tests for ${MAGENTA}$fct${NC}...\n"
			{
				run_test_libc ${TEST_FCT} $fct null
				run_test_libc ${TEST_FCT} $fct ""
				run_test_libc ${TEST_FCT} $fct "This a string to copy"
			} > ${OUTDIR}/output_${TEST_FCT}_${fct}
			printf "All tests for ${MAGENTA}$fct${NC} saved in ${MAGENTA}${OUTDIR}/output_${TEST_FCT}_${fct}${NC}\n"
			if [ ${VERB} -eq 1 ]; then
				printf "Printing ${MAGENTA}${OUTDIR}/output_${TEST_FCT}_${fct}${NC}...\n"
				cat ${OUTDIR}/output_${TEST_FCT}_${fct}
			fi
			printf "\n"
		done
		compare_outputs ${TEST_FCT}
	fi
fi

# strcpy
if [ "${TEST_FCT}" = "strcpy" ] || [ "${ALL}" = "1" ]; then
	TEST_FCT="strcpy"
	RETVAL=0
	compile ${TEST_FCT}
	RETVAL=$?
	if [ ${RETVAL} -eq 0 ]; then # if file compiled without errors
		for fct in ${TEST_FCT} ft_${TEST_FCT}
		do
			printf "Starting tests for ${MAGENTA}$fct${NC}...\n"
			{
				run_test_libc ${TEST_FCT} $fct null null
				run_test_libc ${TEST_FCT} $fct null "AAAAA"
				run_test_libc ${TEST_FCT} $fct 0 null
				run_test_libc ${TEST_FCT} $fct 20 null
				run_test_libc ${TEST_FCT} $fct 0 "AAAA"
				run_test_libc ${TEST_FCT} $fct 1 "AAAA"
				run_test_libc ${TEST_FCT} $fct 10 "AAAAA"
				run_test_libc ${TEST_FCT} $fct 5 "AAAAAAAA"
			} > ${OUTDIR}/output_${TEST_FCT}_${fct}
			printf "All tests for ${MAGENTA}$fct${NC} saved in ${MAGENTA}${OUTDIR}/output_${TEST_FCT}_${fct}${NC}\n"
			if [ ${VERB} -eq 1 ]; then
				printf "Printing ${MAGENTA}${OUTDIR}/output_${TEST_FCT}_${fct}${NC}...\n"
				cat ${OUTDIR}/output_${TEST_FCT}_${fct}
			fi
			printf "\n"
		done
		compare_outputs ${TEST_FCT}
	fi
fi

# strncpy
if [ "${TEST_FCT}" = "strncpy" ] || [ "${ALL}" = "1" ]; then
	TEST_FCT="strncpy"
	RETVAL=0
	compile ${TEST_FCT}
	RETVAL=$?
	if [ ${RETVAL} -eq 0 ]; then # if file compiled without errors
		for fct in ${TEST_FCT} ft_${TEST_FCT}
		do
			printf "Starting tests for ${MAGENTA}$fct${NC}...\n"
			{
				run_test_libc ${TEST_FCT} $fct null null 0
				run_test_libc ${TEST_FCT} $fct null null -1
				run_test_libc ${TEST_FCT} $fct null null 5
				run_test_libc ${TEST_FCT} $fct null "AAAAA" 0
				run_test_libc ${TEST_FCT} $fct null "AAAAA" -1
				run_test_libc ${TEST_FCT} $fct null "AAAAA" 2
				run_test_libc ${TEST_FCT} $fct null "AAAAA" 5
				run_test_libc ${TEST_FCT} $fct null "AAAAA" 10
				run_test_libc ${TEST_FCT} $fct 0 null 0
				run_test_libc ${TEST_FCT} $fct 20 null -1
				run_test_libc ${TEST_FCT} $fct 20 null 2
				run_test_libc ${TEST_FCT} $fct 20 null 5
				run_test_libc ${TEST_FCT} $fct 20 null 30
				run_test_libc ${TEST_FCT} $fct 0 "AAAAA" 0
				run_test_libc ${TEST_FCT} $fct 0 "AAAAA" -1
				run_test_libc ${TEST_FCT} $fct 0 "AAAAA" 2
				run_test_libc ${TEST_FCT} $fct 0 "AAAAA" 10
				run_test_libc ${TEST_FCT} $fct 3 "AAAAA" 0
				run_test_libc ${TEST_FCT} $fct 3 "AAAAA" 1
				run_test_libc ${TEST_FCT} $fct 3 "AAAAA" 2
				run_test_libc ${TEST_FCT} $fct 3 "AAAAA" 5
				run_test_libc ${TEST_FCT} $fct 3 "AAAAA" 10
				run_test_libc ${TEST_FCT} $fct 10 "AAAAA" 0
				run_test_libc ${TEST_FCT} $fct 10 "AAAAA" -1
				run_test_libc ${TEST_FCT} $fct 10 "AAAAA" 3
				run_test_libc ${TEST_FCT} $fct 10 "AAAAA" 5
				run_test_libc ${TEST_FCT} $fct 10 "AAAAA" 8
				run_test_libc ${TEST_FCT} $fct 10 "AAAAA" 10
				run_test_libc ${TEST_FCT} $fct 10 "AAAAA" 15
			} > ${OUTDIR}/output_${TEST_FCT}_${fct}
			printf "All tests for ${MAGENTA}$fct${NC} saved in ${MAGENTA}${OUTDIR}/output_${TEST_FCT}_${fct}${NC}\n"
			if [ ${VERB} -eq 1 ]; then
				printf "Printing ${MAGENTA}${OUTDIR}/output_${TEST_FCT}_${fct}${NC}...\n"
				cat ${OUTDIR}/output_${TEST_FCT}_${fct}
			fi
			printf "\n"
		done
		compare_outputs ${TEST_FCT}
	fi
fi

# strcat
if [ "${TEST_FCT}" = "strcat" ] || [ "${ALL}" = "1" ]; then
	TEST_FCT="strcat"
	RETVAL=0
	compile ${TEST_FCT}
	RETVAL=$?
	if [ ${RETVAL} -eq 0 ]; then # if file compiled without errors
		for fct in ${TEST_FCT} ft_${TEST_FCT}
		do
			printf "Starting tests for ${MAGENTA}$fct${NC}...\n"
			{
				run_test_libc ${TEST_FCT} $fct null null
				run_test_libc ${TEST_FCT} $fct null "AAAAA"
				run_test_libc ${TEST_FCT} $fct 0 null
				run_test_libc ${TEST_FCT} $fct 20 null
				run_test_libc ${TEST_FCT} $fct 0 ""
				run_test_libc ${TEST_FCT} $fct 0 "AAAA"
				run_test_libc ${TEST_FCT} $fct 1 ""
				run_test_libc ${TEST_FCT} $fct 10 ""
				run_test_libc ${TEST_FCT} $fct 10 "AAA"
				run_test_libc ${TEST_FCT} $fct 10 "AAAAAAAA"
			} > ${OUTDIR}/output_${TEST_FCT}_${fct}
			printf "All tests for ${MAGENTA}$fct${NC} saved in ${MAGENTA}${OUTDIR}/output_${TEST_FCT}_${fct}${NC}\n"
			if [ ${VERB} -eq 1 ]; then
				printf "Printing ${MAGENTA}${OUTDIR}/output_${TEST_FCT}_${fct}${NC}...\n"
				cat ${OUTDIR}/output_${TEST_FCT}_${fct}
			fi
			printf "\n"
		done
		compare_outputs ${TEST_FCT}
	fi
fi

# strncat
if [ "${TEST_FCT}" = "strncat" ] || [ "${ALL}" = "1" ]; then
	TEST_FCT="strncat"
	RETVAL=0
	compile ${TEST_FCT}
	RETVAL=$?
	if [ ${RETVAL} -eq 0 ]; then # if file compiled without errors
		for fct in ${TEST_FCT} ft_${TEST_FCT}
		do
			printf "Starting tests for ${MAGENTA}$fct${NC}...\n"
			{
				run_test_libc ${TEST_FCT} $fct null null 0
				run_test_libc ${TEST_FCT} $fct null null -1
				run_test_libc ${TEST_FCT} $fct null null 5
				run_test_libc ${TEST_FCT} $fct null "AAA" 0
				run_test_libc ${TEST_FCT} $fct null "AAA" -1
				run_test_libc ${TEST_FCT} $fct null "AAA" 2
				run_test_libc ${TEST_FCT} $fct null "AAA" 5
				run_test_libc ${TEST_FCT} $fct 0 null 0
				run_test_libc ${TEST_FCT} $fct 0 null -1
				run_test_libc ${TEST_FCT} $fct 0 null 3
				run_test_libc ${TEST_FCT} $fct 0 "AAA" 0
				run_test_libc ${TEST_FCT} $fct 0 "AAA" -1
				run_test_libc ${TEST_FCT} $fct 0 "AAA" 2
				run_test_libc ${TEST_FCT} $fct 0 "AAA" 10
				run_test_libc ${TEST_FCT} $fct 4 "AAA" 0
				run_test_libc ${TEST_FCT} $fct 4 "AAA" 1
				run_test_libc ${TEST_FCT} $fct 4 "AAA" 2
				run_test_libc ${TEST_FCT} $fct 4 "AAA" 5
				run_test_libc ${TEST_FCT} $fct 10 "AAA" 0
				run_test_libc ${TEST_FCT} $fct 10 "AAA" -1
				run_test_libc ${TEST_FCT} $fct 10 "AAA" 2
				run_test_libc ${TEST_FCT} $fct 10 "AAA" 3
				run_test_libc ${TEST_FCT} $fct 10 "AAA" 5
				run_test_libc ${TEST_FCT} $fct 10 "AAA" 10
				run_test_libc ${TEST_FCT} $fct 10 "AAAAAAA" 5
				run_test_libc ${TEST_FCT} $fct 10 "AAAAAAA" 8
				run_test_libc ${TEST_FCT} $fct 10 "AAAAAAAAA" 10
			} > ${OUTDIR}/output_${TEST_FCT}_${fct}
			printf "All tests for ${MAGENTA}$fct${NC} saved in ${MAGENTA}${OUTDIR}/output_${TEST_FCT}_${fct}${NC}\n"
			if [ ${VERB} -eq 1 ]; then
				printf "Printing ${MAGENTA}${OUTDIR}/output_${TEST_FCT}_${fct}${NC}...\n"
				cat ${OUTDIR}/output_${TEST_FCT}_${fct}
			fi
			printf "\n"
		done
		compare_outputs ${TEST_FCT}
	fi
fi

# strlcat
if [ "${TEST_FCT}" = "strlcat" ] || [ "${ALL}" = "1" ]; then
	TEST_FCT="strlcat"
	RETVAL=0
	compile ${TEST_FCT}
	RETVAL=$?
	if [ ${RETVAL} -eq 0 ]; then # if file compiled without errors
		for fct in ${TEST_FCT} ft_${TEST_FCT}
		do
			printf "Starting tests for ${MAGENTA}$fct${NC}...\n"
			{
				run_test_libc ${TEST_FCT} $fct null null 0
				run_test_libc ${TEST_FCT} $fct null null -1
				run_test_libc ${TEST_FCT} $fct null null 5
				run_test_libc ${TEST_FCT} $fct null "AAA" 0
				run_test_libc ${TEST_FCT} $fct null "AAA" -1
				run_test_libc ${TEST_FCT} $fct null "AAA" 2
				run_test_libc ${TEST_FCT} $fct null "AAA" 5
				run_test_libc ${TEST_FCT} $fct 0 null 0
				run_test_libc ${TEST_FCT} $fct 0 null -1
				run_test_libc ${TEST_FCT} $fct 0 null 3
				run_test_libc ${TEST_FCT} $fct 0 "AAA" 0
				run_test_libc ${TEST_FCT} $fct 0 "AAA" -1
				run_test_libc ${TEST_FCT} $fct 0 "AAA" 2
				run_test_libc ${TEST_FCT} $fct 0 "AAA" 10
				run_test_libc ${TEST_FCT} $fct 4 "AAA" 0
				run_test_libc ${TEST_FCT} $fct 4 "AAA" 1
				run_test_libc ${TEST_FCT} $fct 4 "AAA" 2
				run_test_libc ${TEST_FCT} $fct 4 "AAA" 5
				run_test_libc ${TEST_FCT} $fct 10 "AAA" 0
				run_test_libc ${TEST_FCT} $fct 10 "AAA" -1
				run_test_libc ${TEST_FCT} $fct 10 "AAA" 2
				run_test_libc ${TEST_FCT} $fct 10 "AAA" 3
				run_test_libc ${TEST_FCT} $fct 10 "AAA" 5
				run_test_libc ${TEST_FCT} $fct 10 "AAA" 10
				run_test_libc ${TEST_FCT} $fct 10 "AAAAAAA" 5
				run_test_libc ${TEST_FCT} $fct 10 "AAAAAAA" 8
				run_test_libc ${TEST_FCT} $fct 10 "AAAAAAAAA" 10
			} > ${OUTDIR}/output_${TEST_FCT}_${fct}
			printf "All tests for ${MAGENTA}$fct${NC} saved in ${MAGENTA}${OUTDIR}/output_${TEST_FCT}_${fct}${NC}\n"
			if [ ${VERB} -eq 1 ]; then
				printf "Printing ${MAGENTA}${OUTDIR}/output_${TEST_FCT}_${fct}${NC}...\n"
				cat ${OUTDIR}/output_${TEST_FCT}_${fct}
			fi
			printf "\n"
		done
		compare_outputs ${TEST_FCT}
	fi
fi

# strchr
if [ "${TEST_FCT}" = "strchr" ] || [ "${ALL}" = "1" ]; then
	TEST_FCT="strchr"
	RETVAL=0
	compile ${TEST_FCT}
	RETVAL=$?
	if [ ${RETVAL} -eq 0 ]; then # if file compiled without errors
		for fct in ${TEST_FCT} ft_${TEST_FCT}
		do
			printf "Starting tests for ${MAGENTA}$fct${NC}...\n"
			{
				run_test_libc ${TEST_FCT} $fct null 0
				run_test_libc ${TEST_FCT} $fct null 100 #(100 = 'd')
				run_test_libc ${TEST_FCT} $fct null 356 #(356 = 100 + 256 = 'd')
				run_test_libc ${TEST_FCT} $fct "" 0
				run_test_libc ${TEST_FCT} $fct "" 100 #(100 = 'd')
				run_test_libc ${TEST_FCT} $fct "" 356 #(356 = 97 + 256 = 'd')
				run_test_libc ${TEST_FCT} $fct "abcdefghi" 0 #(0 = '\0')
				run_test_libc ${TEST_FCT} $fct "abcdefghi" 100 #(100 = 'd')
				run_test_libc ${TEST_FCT} $fct "abcdefghi" 356 #(356 = 100 + 256 = 'd')
				run_test_libc ${TEST_FCT} $fct "abcdefghi" 36 #(36 = '$')
				run_test_libc ${TEST_FCT} $fct "abcdefghi" 292 #(292 = 36 + 256 = '$')
				run_test_libc ${TEST_FCT} $fct "abcdefghi" ${INT_MIN}
				run_test_libc ${TEST_FCT} $fct "abcdefghi" ${INT_MAX}
			} > ${OUTDIR}/output_${TEST_FCT}_${fct}
			printf "All tests for ${MAGENTA}$fct${NC} saved in ${MAGENTA}${OUTDIR}/output_${TEST_FCT}_${fct}${NC}\n"
			if [ ${VERB} -eq 1 ]; then
				printf "Printing ${MAGENTA}${OUTDIR}/output_${TEST_FCT}_${fct}${NC}...\n"
				cat ${OUTDIR}/output_${TEST_FCT}_${fct}
			fi
			printf "\n"
		done
		compare_outputs ${TEST_FCT}
	fi
fi

# strrchr
if [ "${TEST_FCT}" = "strrchr" ] || [ "${ALL}" = "1" ]; then
	TEST_FCT="strrchr"
	RETVAL=0
	compile ${TEST_FCT}
	RETVAL=$?
	if [ ${RETVAL} -eq 0 ]; then # if file compiled without errors
		for fct in ${TEST_FCT} ft_${TEST_FCT}
		do
			printf "Starting tests for ${MAGENTA}$fct${NC}...\n"
			{
				run_test_libc ${TEST_FCT} $fct null 0
				run_test_libc ${TEST_FCT} $fct null 100 #(100 = 'd')
				run_test_libc ${TEST_FCT} $fct null 356 #(356 = 100 + 256 = 'd')
				run_test_libc ${TEST_FCT} $fct "" 0
				run_test_libc ${TEST_FCT} $fct "" 100 #(100 = 'd')
				run_test_libc ${TEST_FCT} $fct "" 356 #(356 = 97 + 256 = 'd')
				run_test_libc ${TEST_FCT} $fct "abcdefghi" 0 #(0 = '\0')
				run_test_libc ${TEST_FCT} $fct "abcdefghi" 100 #(100 = 'd')
				run_test_libc ${TEST_FCT} $fct "abcdefghi" 356 #(356 = 100 + 256 = 'd')
				run_test_libc ${TEST_FCT} $fct "abcdefghi" 36 #(36 = '$')
				run_test_libc ${TEST_FCT} $fct "abcdefghi" 292 #(292 = 36 + 256 = '$')
				run_test_libc ${TEST_FCT} $fct "abcdefghi" ${INT_MIN}
				run_test_libc ${TEST_FCT} $fct "abcdefghi" ${INT_MAX}
				run_test_libc ${TEST_FCT} $fct "abcdefdhi" 0 #(0 = '\0')
				run_test_libc ${TEST_FCT} $fct "abcdefdhi" 100 #(100 = 'd')
				run_test_libc ${TEST_FCT} $fct "abcdefdhi" 356 #(356 = 100 + 256 = 'd')
				run_test_libc ${TEST_FCT} $fct "abcdefdhi" 36 #(36 = '$')
				run_test_libc ${TEST_FCT} $fct "abcdefdhi" 292 #(292 = 36 + 256 = '$')
				run_test_libc ${TEST_FCT} $fct "ddddddddd" 0 #(0 = '\0')
				run_test_libc ${TEST_FCT} $fct "ddddddddd" 100 #(100 = 'd')
				run_test_libc ${TEST_FCT} $fct "ddddddddd" 356 #(356 = 100 + 256 = 'd')
				run_test_libc ${TEST_FCT} $fct "ddddddddd" 36 #(36 = '$')
				run_test_libc ${TEST_FCT} $fct "ddddddddd" 292 #(292 = 36 + 256 = '$')
			} > ${OUTDIR}/output_${TEST_FCT}_${fct}
			printf "All tests for ${MAGENTA}$fct${NC} saved in ${MAGENTA}${OUTDIR}/output_${TEST_FCT}_${fct}${NC}\n"
			if [ ${VERB} -eq 1 ]; then
				printf "Printing ${MAGENTA}${OUTDIR}/output_${TEST_FCT}_${fct}${NC}...\n"
				cat ${OUTDIR}/output_${TEST_FCT}_${fct}
			fi
			printf "\n"
		done
		compare_outputs ${TEST_FCT}
	fi
fi

# strstr
if [ "${TEST_FCT}" = "strstr" ] || [ "${ALL}" = "1" ]; then
	TEST_FCT="strstr"
	RETVAL=0
	compile ${TEST_FCT}
	RETVAL=$?
	if [ ${RETVAL} -eq 0 ]; then # if file compiled without errors
		for fct in ${TEST_FCT} ft_${TEST_FCT}
		do
			printf "Starting tests for ${MAGENTA}$fct${NC}...\n"
			{
				run_test_libc ${TEST_FCT} $fct null null
				run_test_libc ${TEST_FCT} $fct null "abcd"
				run_test_libc ${TEST_FCT} $fct "abcdefg" null
				run_test_libc ${TEST_FCT} $fct "" ""
				run_test_libc ${TEST_FCT} $fct "abcdefg" ""
				run_test_libc ${TEST_FCT} $fct "abcdefg" "ab"
				run_test_libc ${TEST_FCT} $fct "abcdefg" "cde"
				run_test_libc ${TEST_FCT} $fct "abcdefg" "fg"
				run_test_libc ${TEST_FCT} $fct "abcdefg" "cdf"
				run_test_libc ${TEST_FCT} $fct "abcdefg" "efgh"
				run_test_libc ${TEST_FCT} $fct "aaaaaaa" "aaa"
				run_test_libc ${TEST_FCT} $fct "aabaaba" "aba"
				run_test_libc ${TEST_FCT} $fct "abcdef" "abcdef"
			} > ${OUTDIR}/output_${TEST_FCT}_${fct}
			printf "All tests for ${MAGENTA}$fct${NC} saved in ${MAGENTA}${OUTDIR}/output_${TEST_FCT}_${fct}${NC}\n"
			if [ ${VERB} -eq 1 ]; then
				printf "Printing ${MAGENTA}${OUTDIR}/output_${TEST_FCT}_${fct}${NC}...\n"
				cat ${OUTDIR}/output_${TEST_FCT}_${fct}
			fi
			printf "\n"
		done
		compare_outputs ${TEST_FCT}
	fi
fi

# strnstr
if [ "${TEST_FCT}" = "strnstr" ] || [ "${ALL}" = "1" ]; then
	TEST_FCT="strnstr"
	RETVAL=0
	compile ${TEST_FCT}
	RETVAL=$?
	if [ ${RETVAL} -eq 0 ]; then # if file compiled without errors
		for fct in ${TEST_FCT} ft_${TEST_FCT}
		do
			printf "Starting tests for ${MAGENTA}$fct${NC}...\n"
			{
				run_test_libc ${TEST_FCT} $fct null null 0
				run_test_libc ${TEST_FCT} $fct null null -1
				run_test_libc ${TEST_FCT} $fct null null 5
				run_test_libc ${TEST_FCT} $fct null "abcd" 0
				run_test_libc ${TEST_FCT} $fct null "abcd" -1
				run_test_libc ${TEST_FCT} $fct null "abcd" 5
				run_test_libc ${TEST_FCT} $fct "" "" 0
				run_test_libc ${TEST_FCT} $fct "" "" -1
				run_test_libc ${TEST_FCT} $fct "" "" 1
				run_test_libc ${TEST_FCT} $fct "" "" 2
				run_test_libc ${TEST_FCT} $fct "abcdefg" null 0
				run_test_libc ${TEST_FCT} $fct "abcdefg" null -1
				run_test_libc ${TEST_FCT} $fct "abcdefg" null 5
				run_test_libc ${TEST_FCT} $fct "abcdefg" "" 0
				run_test_libc ${TEST_FCT} $fct "abcdefg" "" -1
				run_test_libc ${TEST_FCT} $fct "abcdefg" "" 5
				run_test_libc ${TEST_FCT} $fct "abcdefg" "ab" 0
				run_test_libc ${TEST_FCT} $fct "abcdefg" "ab" -1
				run_test_libc ${TEST_FCT} $fct "abcdefg" "ab" 2
				run_test_libc ${TEST_FCT} $fct "abcdefg" "ab" 4
				run_test_libc ${TEST_FCT} $fct "abcdefg" "cde" 0
				run_test_libc ${TEST_FCT} $fct "abcdefg" "cde" 3
				run_test_libc ${TEST_FCT} $fct "abcdefg" "cde" 4
				run_test_libc ${TEST_FCT} $fct "abcdefg" "fg" 0
				run_test_libc ${TEST_FCT} $fct "abcdefg" "fg" 2
				run_test_libc ${TEST_FCT} $fct "abcdefg" "fg" 4
				run_test_libc ${TEST_FCT} $fct "abcdefg" "cdf" 0
				run_test_libc ${TEST_FCT} $fct "abcdefg" "cdf" 3
				run_test_libc ${TEST_FCT} $fct "abcdefg" "cdf" 2
				run_test_libc ${TEST_FCT} $fct "abcdefg" "efgh" 4
				run_test_libc ${TEST_FCT} $fct "abcdefg" "efgh" 3
				run_test_libc ${TEST_FCT} $fct "aaaaaaa" "aaa" 1
				run_test_libc ${TEST_FCT} $fct "aaaaaaa" "aaa" 4
				run_test_libc ${TEST_FCT} $fct "aaaaaaa" "aaa" 6
				run_test_libc ${TEST_FCT} $fct "aabaaba" "aba" 0
				run_test_libc ${TEST_FCT} $fct "aabaaba" "aba" 2
				run_test_libc ${TEST_FCT} $fct "aabaaba" "aba" 5
				run_test_libc ${TEST_FCT} $fct "abcdef" "abcdef" 0
				run_test_libc ${TEST_FCT} $fct "abcdef" "abcdef" 2
				run_test_libc ${TEST_FCT} $fct "abcdef" "abcdef" 4
				run_test_libc ${TEST_FCT} $fct "abcdef" "abcdef" 6
				run_test_libc ${TEST_FCT} $fct "abcdef" "abcdef" 7
			} > ${OUTDIR}/output_${TEST_FCT}_${fct}
			printf "All tests for ${MAGENTA}$fct${NC} saved in ${MAGENTA}${OUTDIR}/output_${TEST_FCT}_${fct}${NC}\n"
			if [ ${VERB} -eq 1 ]; then
				printf "Printing ${MAGENTA}${OUTDIR}/output_${TEST_FCT}_${fct}${NC}...\n"
				cat ${OUTDIR}/output_${TEST_FCT}_${fct}
			fi
			printf "\n"
		done
		compare_outputs ${TEST_FCT}
	fi
fi

# strcmp
if [ "${TEST_FCT}" = "strcmp" ] || [ "${ALL}" = "1" ]; then
	TEST_FCT="strcmp"
	RETVAL=0
	compile ${TEST_FCT}
	RETVAL=$?
	if [ ${RETVAL} -eq 0 ]; then # if file compiled without errors
		for fct in ${TEST_FCT} ft_${TEST_FCT}
		do
			printf "Starting tests for ${MAGENTA}$fct${NC}...\n"
			{
				run_test_libc ${TEST_FCT} $fct null null
				run_test_libc ${TEST_FCT} $fct null ""
				run_test_libc ${TEST_FCT} $fct null "abcd"
				run_test_libc ${TEST_FCT} $fct "abcd" null
				run_test_libc ${TEST_FCT} $fct "" null
				run_test_libc ${TEST_FCT} $fct "" ""
				run_test_libc ${TEST_FCT} $fct "abcd" "a"
				run_test_libc ${TEST_FCT} $fct "abcd" "abc"
				run_test_libc ${TEST_FCT} $fct "abcd" "abcd"
				run_test_libc ${TEST_FCT} $fct "abcd" "abcde"
				run_test_libc ${TEST_FCT} $fct "abcd" "abce"
				run_test_libc ${TEST_FCT} $fct "abcd" "bc"
				run_test_libc ${TEST_FCT} $fct "abcd" "bcd"
				run_test_libc ${TEST_FCT} $fct "abc" "ABC"
			} > ${OUTDIR}/output_${TEST_FCT}_${fct}
			printf "All tests for ${MAGENTA}$fct${NC} saved in ${MAGENTA}${OUTDIR}/output_${TEST_FCT}_${fct}${NC}\n"
			if [ ${VERB} -eq 1 ]; then
				printf "Printing ${MAGENTA}${OUTDIR}/output_${TEST_FCT}_${fct}${NC}...\n"
				cat ${OUTDIR}/output_${TEST_FCT}_${fct}
			fi
			printf "\n"
		done
		compare_outputs ${TEST_FCT}
	fi
fi

# strncmp
if [ "${TEST_FCT}" = "strncmp" ] || [ "${ALL}" = "1" ]; then
	TEST_FCT="strncmp"
	RETVAL=0
	compile ${TEST_FCT}
	RETVAL=$?
	if [ ${RETVAL} -eq 0 ]; then # if file compiled without errors
		for fct in ${TEST_FCT} ft_${TEST_FCT}
		do
			printf "Starting tests for ${MAGENTA}$fct${NC}...\n"
			{
				run_test_libc ${TEST_FCT} $fct null null 0
				run_test_libc ${TEST_FCT} $fct null null -1
				run_test_libc ${TEST_FCT} $fct null null 5
				run_test_libc ${TEST_FCT} $fct null "" 0
				run_test_libc ${TEST_FCT} $fct null "" -1
				run_test_libc ${TEST_FCT} $fct null "" 5
				run_test_libc ${TEST_FCT} $fct null "abcd" 0
				run_test_libc ${TEST_FCT} $fct null "abcd" -1
				run_test_libc ${TEST_FCT} $fct null "abcd" 2
				run_test_libc ${TEST_FCT} $fct null "abcd" 10
				run_test_libc ${TEST_FCT} $fct "abcd" null 0
				run_test_libc ${TEST_FCT} $fct "abcd" null -1
				run_test_libc ${TEST_FCT} $fct "abcd" null 2
				run_test_libc ${TEST_FCT} $fct "abcd" null 5
				run_test_libc ${TEST_FCT} $fct "" null 0
				run_test_libc ${TEST_FCT} $fct "" null -1
				run_test_libc ${TEST_FCT} $fct "" null 2
				run_test_libc ${TEST_FCT} $fct "" null 10
				run_test_libc ${TEST_FCT} $fct "" "" 0
				run_test_libc ${TEST_FCT} $fct "" "" 1
				run_test_libc ${TEST_FCT} $fct "" "" -1
				run_test_libc ${TEST_FCT} $fct "" "" 2
				run_test_libc ${TEST_FCT} $fct "abcd" "a" 0
				run_test_libc ${TEST_FCT} $fct "abcd" "a" -1
				run_test_libc ${TEST_FCT} $fct "abcd" "a" 1
				run_test_libc ${TEST_FCT} $fct "abcd" "a" 2
				run_test_libc ${TEST_FCT} $fct "abcd" "a" 5
				run_test_libc ${TEST_FCT} $fct "abcd" "abc" 0
				run_test_libc ${TEST_FCT} $fct "abcd" "abc" 1
				run_test_libc ${TEST_FCT} $fct "abcd" "abc" 2
				run_test_libc ${TEST_FCT} $fct "abcd" "abc" 3
				run_test_libc ${TEST_FCT} $fct "abcd" "abc" 5
				run_test_libc ${TEST_FCT} $fct "abcd" "abcdef" 0
				run_test_libc ${TEST_FCT} $fct "abcd" "abcdef" 2
				run_test_libc ${TEST_FCT} $fct "abcd" "abcdef" 4
				run_test_libc ${TEST_FCT} $fct "abcd" "abcdef" 6
				run_test_libc ${TEST_FCT} $fct "abcd" "abcdef" 10
			} > ${OUTDIR}/output_${TEST_FCT}_${fct}
			printf "All tests for ${MAGENTA}$fct${NC} saved in ${MAGENTA}${OUTDIR}/output_${TEST_FCT}_${fct}${NC}\n"
			if [ ${VERB} -eq 1 ]; then
				printf "Printing ${MAGENTA}${OUTDIR}/output_${TEST_FCT}_${fct}${NC}...\n"
				cat ${OUTDIR}/output_${TEST_FCT}_${fct}
			fi
			printf "\n"
		done
		compare_outputs ${TEST_FCT}
	fi
fi

# atoi
if [ "${TEST_FCT}" = "atoi" ] || [ "${ALL}" = "1" ]; then
	TEST_FCT="atoi"
	RETVAL=0
	compile ${TEST_FCT}
	RETVAL=$?
	if [ ${RETVAL} -eq 0 ]; then # if file compiled without errors
		for fct in ${TEST_FCT} ft_${TEST_FCT}
		do
			printf "Starting tests for ${MAGENTA}$fct${NC}...\n"
			{
				run_test_libc ${TEST_FCT} $fct null
				run_test_libc ${TEST_FCT} $fct ""
				run_test_libc ${TEST_FCT} $fct "\t +0A"
				run_test_libc ${TEST_FCT} $fct "\t -0.123"
				run_test_libc ${TEST_FCT} $fct "    -32  "
				run_test_libc ${TEST_FCT} $fct "    +32  "
				run_test_libc ${TEST_FCT} $fct "    ++32  "
				run_test_libc ${TEST_FCT} $fct "    -+32  "
				run_test_libc ${TEST_FCT} $fct "    +-32  "
				run_test_libc ${TEST_FCT} $fct "    +0377  "
				run_test_libc ${TEST_FCT} $fct "0377"
				run_test_libc ${TEST_FCT} $fct "    +0377  "
				run_test_libc ${TEST_FCT} $fct "    -0377  "
				run_test_libc ${TEST_FCT} $fct "    -00377  "
				run_test_libc ${TEST_FCT} $fct "0x7FFF"
				run_test_libc ${TEST_FCT} $fct " +0x7FFF"
				run_test_libc ${TEST_FCT} $fct " +0x7FFF"
				run_test_libc ${TEST_FCT} $fct " AAA+233BB"
				run_test_libc ${TEST_FCT} $fct " A+AA+233B"
				run_test_libc ${TEST_FCT} $fct " ABC-233F"
				run_test_libc ${TEST_FCT} $fct "   -2147483648  "
				run_test_libc ${TEST_FCT} $fct "   2147483647  "
				run_test_libc ${TEST_FCT} $fct "   2147483648  "
				run_test_libc ${TEST_FCT} $fct "   -2147483649  "
				run_test_libc ${TEST_FCT} $fct "   21474836470  "
				run_test_libc ${TEST_FCT} $fct "   -21474836480  "
				run_test_libc ${TEST_FCT} $fct " +999999999999999999"
				#run_test_libc ${TEST_FCT} $fct " +9999999999999999999" #fails
			} > ${OUTDIR}/output_${TEST_FCT}_${fct}
			printf "All tests for ${MAGENTA}$fct${NC} saved in ${MAGENTA}${OUTDIR}/output_${TEST_FCT}_${fct}${NC}\n"
			if [ ${VERB} -eq 1 ]; then
				printf "Printing ${MAGENTA}${OUTDIR}/output_${TEST_FCT}_${fct}${NC}...\n"
				cat ${OUTDIR}/output_${TEST_FCT}_${fct}
			fi
			printf "\n"
		done
		compare_outputs ${TEST_FCT}
	fi
fi

# isalpha
if [ "${TEST_FCT}" = "isalpha" ] || [ "${ALL}" = "1" ]; then
	TEST_FCT="isalpha"
	RETVAL=0
	compile ${TEST_FCT}
	RETVAL=$?
	if [ ${RETVAL} -eq 0 ]; then # if file compiled without errors
		for fct in ${TEST_FCT} ft_${TEST_FCT}
		do
			printf "Starting tests for ${MAGENTA}$fct${NC}...\n"
			{
				run_test_libc ${TEST_FCT} $fct ''
				run_test_libc ${TEST_FCT} $fct '0'
				run_test_libc ${TEST_FCT} $fct '%'
				run_test_libc ${TEST_FCT} $fct 'a'
				run_test_libc ${TEST_FCT} $fct 'A'
				run_test_libc ${TEST_FCT} $fct 65
				run_test_libc ${TEST_FCT} $fct 2625 # 2625 = 65 + 256 * 10
				run_test_libc ${TEST_FCT} $fct 123456
				run_test_libc ${TEST_FCT} $fct ${INT_MIN}
				run_test_libc ${TEST_FCT} $fct ${INT_MAX}
			} > ${OUTDIR}/output_${TEST_FCT}_${fct}
			printf "All tests for ${MAGENTA}$fct${NC} saved in ${MAGENTA}${OUTDIR}/output_${TEST_FCT}_${fct}${NC}\n"
			if [ ${VERB} -eq 1 ]; then
				printf "Printing ${MAGENTA}${OUTDIR}/output_${TEST_FCT}_${fct}${NC}...\n"
				cat ${OUTDIR}/output_${TEST_FCT}_${fct}
			fi
			printf "\n"
		done
		compare_outputs ${TEST_FCT}
	fi
fi

# isdigit
if [ "${TEST_FCT}" = "isdigit" ] || [ "${ALL}" = "1" ]; then
	TEST_FCT="isdigit"
	RETVAL=0
	compile ${TEST_FCT}
	RETVAL=$?
	if [ ${RETVAL} -eq 0 ]; then # if file compiled without errors
		for fct in ${TEST_FCT} ft_${TEST_FCT}
		do
			printf "Starting tests for ${MAGENTA}$fct${NC}...\n"
			{
				run_test_libc ${TEST_FCT} $fct ''
				run_test_libc ${TEST_FCT} $fct '0'
				run_test_libc ${TEST_FCT} $fct '1'
				run_test_libc ${TEST_FCT} $fct '5'
				run_test_libc ${TEST_FCT} $fct '9'
				run_test_libc ${TEST_FCT} $fct '%'
				run_test_libc ${TEST_FCT} $fct 'a'
				run_test_libc ${TEST_FCT} $fct 'A'
				run_test_libc ${TEST_FCT} $fct 65
				run_test_libc ${TEST_FCT} $fct 2625 # 2625 = 65 + 256 * 10
				run_test_libc ${TEST_FCT} $fct 123456
				run_test_libc ${TEST_FCT} $fct ${INT_MIN}
				run_test_libc ${TEST_FCT} $fct ${INT_MAX}
			} > ${OUTDIR}/output_${TEST_FCT}_${fct}
			printf "All tests for ${MAGENTA}$fct${NC} saved in ${MAGENTA}${OUTDIR}/output_${TEST_FCT}_${fct}${NC}\n"
			if [ ${VERB} -eq 1 ]; then
				printf "Printing ${MAGENTA}${OUTDIR}/output_${TEST_FCT}_${fct}${NC}...\n"
				cat ${OUTDIR}/output_${TEST_FCT}_${fct}
			fi
			printf "\n"
		done
		compare_outputs ${TEST_FCT}
	fi
fi

# isalnum
if [ "${TEST_FCT}" = "isalnum" ] || [ "${ALL}" = "1" ]; then
	TEST_FCT="isalnum"
	RETVAL=0
	compile ${TEST_FCT}
	RETVAL=$?
	if [ ${RETVAL} -eq 0 ]; then # if file compiled without errors
		for fct in ${TEST_FCT} ft_${TEST_FCT}
		do
			printf "Starting tests for ${MAGENTA}$fct${NC}...\n"
			{
				run_test_libc ${TEST_FCT} $fct ''
				run_test_libc ${TEST_FCT} $fct '0'
				run_test_libc ${TEST_FCT} $fct '1'
				run_test_libc ${TEST_FCT} $fct '5'
				run_test_libc ${TEST_FCT} $fct '9'
				run_test_libc ${TEST_FCT} $fct '%'
				run_test_libc ${TEST_FCT} $fct 'a'
				run_test_libc ${TEST_FCT} $fct 'A'
				run_test_libc ${TEST_FCT} $fct 65
				run_test_libc ${TEST_FCT} $fct 2625 # 2625 = 65 + 256 * 10
				run_test_libc ${TEST_FCT} $fct 123456
				run_test_libc ${TEST_FCT} $fct ${INT_MIN}
				run_test_libc ${TEST_FCT} $fct ${INT_MAX}
			} > ${OUTDIR}/output_${TEST_FCT}_${fct}
			printf "All tests for ${MAGENTA}$fct${NC} saved in ${MAGENTA}${OUTDIR}/output_${TEST_FCT}_${fct}${NC}\n"
			if [ ${VERB} -eq 1 ]; then
				printf "Printing ${MAGENTA}${OUTDIR}/output_${TEST_FCT}_${fct}${NC}...\n"
				cat ${OUTDIR}/output_${TEST_FCT}_${fct}
			fi
			printf "\n"
		done
		compare_outputs ${TEST_FCT}
	fi
fi

# isascii
if [ "${TEST_FCT}" = "isascii" ] || [ "${ALL}" = "1" ]; then
	TEST_FCT="isascii"
	RETVAL=0
	compile ${TEST_FCT}
	RETVAL=$?
	if [ ${RETVAL} -eq 0 ]; then # if file compiled without errors
		for fct in ${TEST_FCT} ft_${TEST_FCT}
		do
			printf "Starting tests for ${MAGENTA}$fct${NC}...\n"
			{
				run_test_libc ${TEST_FCT} $fct ''
				run_test_libc ${TEST_FCT} $fct '0'
				run_test_libc ${TEST_FCT} $fct '1'
				run_test_libc ${TEST_FCT} $fct '5'
				run_test_libc ${TEST_FCT} $fct '9'
				run_test_libc ${TEST_FCT} $fct '%'
				run_test_libc ${TEST_FCT} $fct 'a'
				run_test_libc ${TEST_FCT} $fct 'A'
				run_test_libc ${TEST_FCT} $fct 65
				run_test_libc ${TEST_FCT} $fct 2625 # 2625 = 65 + 256 * 10
				run_test_libc ${TEST_FCT} $fct 123456
				run_test_libc ${TEST_FCT} $fct ${INT_MIN}
				run_test_libc ${TEST_FCT} $fct ${INT_MAX}
			} > ${OUTDIR}/output_${TEST_FCT}_${fct}
			printf "All tests for ${MAGENTA}$fct${NC} saved in ${MAGENTA}${OUTDIR}/output_${TEST_FCT}_${fct}${NC}\n"
			if [ ${VERB} -eq 1 ]; then
				printf "Printing ${MAGENTA}${OUTDIR}/output_${TEST_FCT}_${fct}${NC}...\n"
				cat ${OUTDIR}/output_${TEST_FCT}_${fct}
			fi
			printf "\n"
		done
		compare_outputs ${TEST_FCT}
	fi
fi

# isprint
if [ "${TEST_FCT}" = "isprint" ] || [ "${ALL}" = "1" ]; then
	TEST_FCT="isprint"
	RETVAL=0
	compile ${TEST_FCT}
	RETVAL=$?
	if [ ${RETVAL} -eq 0 ]; then # if file compiled without errors
		for fct in ${TEST_FCT} ft_${TEST_FCT}
		do
			printf "Starting tests for ${MAGENTA}$fct${NC}...\n"
			{
				run_test_libc ${TEST_FCT} $fct ''
				run_test_libc ${TEST_FCT} $fct '\t'
				run_test_libc ${TEST_FCT} $fct '\v'
				run_test_libc ${TEST_FCT} $fct '\n'
				run_test_libc ${TEST_FCT} $fct ' '
				run_test_libc ${TEST_FCT} $fct '0'
				run_test_libc ${TEST_FCT} $fct '1'
				run_test_libc ${TEST_FCT} $fct '5'
				run_test_libc ${TEST_FCT} $fct '9'
				run_test_libc ${TEST_FCT} $fct '%'
				run_test_libc ${TEST_FCT} $fct 'a'
				run_test_libc ${TEST_FCT} $fct 'A'
				run_test_libc ${TEST_FCT} $fct 65
				run_test_libc ${TEST_FCT} $fct 123
				run_test_libc ${TEST_FCT} $fct 127
				run_test_libc ${TEST_FCT} $fct 2625 # 2625 = 65 + 256 * 10
				run_test_libc ${TEST_FCT} $fct 123456
				run_test_libc ${TEST_FCT} $fct ${INT_MIN}
				run_test_libc ${TEST_FCT} $fct ${INT_MAX}
			} > ${OUTDIR}/output_${TEST_FCT}_${fct}
			printf "All tests for ${MAGENTA}$fct${NC} saved in ${MAGENTA}${OUTDIR}/output_${TEST_FCT}_${fct}${NC}\n"
			if [ ${VERB} -eq 1 ]; then
				printf "Printing ${MAGENTA}${OUTDIR}/output_${TEST_FCT}_${fct}${NC}...\n"
				cat ${OUTDIR}/output_${TEST_FCT}_${fct}
			fi
			printf "\n"
		done
		compare_outputs ${TEST_FCT}
	fi
fi

# toupper
if [ "${TEST_FCT}" = "toupper" ] || [ "${ALL}" = "1" ]; then
	TEST_FCT="toupper"
	RETVAL=0
	compile ${TEST_FCT}
	RETVAL=$?
	if [ ${RETVAL} -eq 0 ]; then # if file compiled without errors
		for fct in ${TEST_FCT} ft_${TEST_FCT}
		do
			printf "Starting tests for ${MAGENTA}$fct${NC}...\n"
			{
				run_test_libc ${TEST_FCT} $fct ''
				run_test_libc ${TEST_FCT} $fct '\t'
				run_test_libc ${TEST_FCT} $fct '\v'
				run_test_libc ${TEST_FCT} $fct '\n'
				run_test_libc ${TEST_FCT} $fct ' '
				run_test_libc ${TEST_FCT} $fct '0'
				run_test_libc ${TEST_FCT} $fct '1'
				run_test_libc ${TEST_FCT} $fct '5'
				run_test_libc ${TEST_FCT} $fct '9'
				run_test_libc ${TEST_FCT} $fct '%'
				run_test_libc ${TEST_FCT} $fct 'a'
				run_test_libc ${TEST_FCT} $fct 'n'
				run_test_libc ${TEST_FCT} $fct 'z'
				run_test_libc ${TEST_FCT} $fct 'A'
				run_test_libc ${TEST_FCT} $fct 65
				run_test_libc ${TEST_FCT} $fct 123
				run_test_libc ${TEST_FCT} $fct 127
				run_test_libc ${TEST_FCT} $fct 2625 # 2625 = 65 + 256 * 10
				run_test_libc ${TEST_FCT} $fct 123456
				run_test_libc ${TEST_FCT} $fct ${INT_MIN}
				run_test_libc ${TEST_FCT} $fct ${INT_MAX}
			} > ${OUTDIR}/output_${TEST_FCT}_${fct}
			printf "All tests for ${MAGENTA}$fct${NC} saved in ${MAGENTA}${OUTDIR}/output_${TEST_FCT}_${fct}${NC}\n"
			if [ ${VERB} -eq 1 ]; then
				printf "Printing ${MAGENTA}${OUTDIR}/output_${TEST_FCT}_${fct}${NC}...\n"
				cat ${OUTDIR}/output_${TEST_FCT}_${fct}
			fi
			printf "\n"
		done
		compare_outputs ${TEST_FCT}
	fi
fi

# tolower
if [ "${TEST_FCT}" = "tolower" ] || [ "${ALL}" = "1" ]; then
	TEST_FCT="tolower"
	RETVAL=0
	compile ${TEST_FCT}
	RETVAL=$?
	if [ ${RETVAL} -eq 0 ]; then # if file compiled without errors
		for fct in ${TEST_FCT} ft_${TEST_FCT}
		do
			printf "Starting tests for ${MAGENTA}$fct${NC}...\n"
			{
				run_test_libc ${TEST_FCT} $fct ''
				run_test_libc ${TEST_FCT} $fct '\t'
				run_test_libc ${TEST_FCT} $fct '\v'
				run_test_libc ${TEST_FCT} $fct '\n'
				run_test_libc ${TEST_FCT} $fct ' '
				run_test_libc ${TEST_FCT} $fct '0'
				run_test_libc ${TEST_FCT} $fct '1'
				run_test_libc ${TEST_FCT} $fct '5'
				run_test_libc ${TEST_FCT} $fct '9'
				run_test_libc ${TEST_FCT} $fct '%'
				run_test_libc ${TEST_FCT} $fct 'a'
				run_test_libc ${TEST_FCT} $fct 'n'
				run_test_libc ${TEST_FCT} $fct 'z'
				run_test_libc ${TEST_FCT} $fct 'A'
				run_test_libc ${TEST_FCT} $fct 'N'
				run_test_libc ${TEST_FCT} $fct 'Z'
				run_test_libc ${TEST_FCT} $fct 65
				run_test_libc ${TEST_FCT} $fct 123
				run_test_libc ${TEST_FCT} $fct 127
				run_test_libc ${TEST_FCT} $fct 2625 # 2625 = 65 + 256 * 10
				run_test_libc ${TEST_FCT} $fct 123456
				run_test_libc ${TEST_FCT} $fct ${INT_MIN}
				run_test_libc ${TEST_FCT} $fct ${INT_MAX}
			} > ${OUTDIR}/output_${TEST_FCT}_${fct}
			printf "All tests for ${MAGENTA}$fct${NC} saved in ${MAGENTA}${OUTDIR}/output_${TEST_FCT}_${fct}${NC}\n"
			if [ ${VERB} -eq 1 ]; then
				printf "Printing ${MAGENTA}${OUTDIR}/output_${TEST_FCT}_${fct}${NC}...\n"
				cat ${OUTDIR}/output_${TEST_FCT}_${fct}
			fi
			printf "\n"
		done
		compare_outputs ${TEST_FCT}
	fi
fi

# ft_memalloc
if [ "${TEST_FCT}" = "ft_memalloc" ] || [ "${ALL}" = "2" ]; then
	TEST_FCT="ft_memalloc"
	RETVAL=0
	compile ${TEST_FCT}
	RETVAL=$?
	if [ ${RETVAL} -eq 0 ]; then # if file compiled without errors
		printf "Starting tests for ${MAGENTA}$fct${NC}...\n"
		{
			run_test_other ${TEST_FCT} 0
			run_test_other ${TEST_FCT} 2
			run_test_other ${TEST_FCT} 10
		} > ${OUTDIR}/output_${TEST_FCT}_${fct}
		printf "All tests for ${MAGENTA}$fct${NC} saved in ${MAGENTA}${OUTDIR}/output_${TEST_FCT}_${fct}${NC}\n"
		if [ ${VERB} -eq 1 ]; then
			printf "Printing ${MAGENTA}${OUTDIR}/output_${TEST_FCT}_${fct}${NC}...\n"
			cat ${OUTDIR}/output_${TEST_FCT}_${fct}
		fi
		printf "\n"
	fi
fi


# Display summary
if [ "${ALL}" -eq 1 ]; then
print_summary
fi
