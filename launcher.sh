# Display usage
if [[ $# -eq 0 ]]; then
	printf "%s\n" "Error: missing argument"
	printf "%s\n" "Usage: ./launcher.sh function_name"
fi

# memset
if [ "$1" = "memset" ]; then
	gcc -Wall -Werror -Wextra  -I. -L. -lft tests/base_memset_test.c -o out/base_memset_test
	function base_test_memset {
		{
		./out/base_memset_test $1 $2 $3 $4
		ERRCODE=$?
		} 2> /dev/null
		if [ ${ERRCODE} -eq 0 ]; then
			 printf "%s(%s, %d, %d): %s\n" $1 $2 $3 $4 "No error (0)" 
		elif [ ${ERRCODE} -eq 139 ]; then
			 printf "%s(%s, %d, %d): %s\n" $1 $2 $3 $4 "Segfault (${ERRCODE})"
		elif [ ${ERRCODE} -eq 134 ]; then
			 printf "%s(%s, %d, %d): %s\n" $1 $2 $3 $4 "Abort (${ERRCODE})"
		fi
	}
	for fct in memset
	do
		if [ fct = ft_memset ]; then
			FT_FCT="ft_memset"
		elif [ fct = memset ]; then
			FCT="memset"
		fi
		printf "" > $fct\_errors.txt
		for b in NULL char[]
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
fi
