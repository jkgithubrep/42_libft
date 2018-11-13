if [[ $# -eq 0 ]]; then
	printf "%s\n" "Error: missing argument"
	printf "%s\n" "Usage: ./launcher.sh function_name"
fi

# ft_memset
if [ "$1" = "memset" ]; then
gcc -Wall -Werror -Wextra  -I. -L. -lft tests/ft_memset_test.c -o out/ft_memset_test
function test_memset {
	./out/ft_memset_test $1 $2
	echo
}
test_memset 147 10
test_memset 23423 23
test_memset 93 0
test_memset 93 34
fi

# base_memset
if [ "$1" = "base_memset" ]; then
	gcc -Wall -Werror -Wextra  -I. -L. -lft tests/base_memset_test.c -o out/base_memset_test
	function base_test_memset {
		printf "(%s, %d, %d): " $1 $2 $3
		./out/base_memset_test $1 $2 $3 
		ERRCODE=$?
		exec 2>&1
		if [ ${ERRCODE} -eq 0 ]; then
			echo "No error" 
		fi
	}
	for b in NULL int[] long[]
	do
		for char in 0 98 -36 288
		do
			for len in -2 0 3 140
			do
				base_test_memset $b $char $len
			done
		done
	done
fi

# test
if [ "$1" = "test" ]; then
printf "%s\n" "$1base"
fi
