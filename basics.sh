#!/bin/sh

NC="\e[0m"
BOLD="\e[1m"
UNDERLINE="\e[4m"

libc="memset bzero memcpy memccpy memmove memchr memcmp strlen strdup strcpy strncpy strcat strncat strlcat strchr strrchr strstr strnstr strcmp strncmp atoi isalpha isdigit isalnum isascii isprint toupper tolower"
supp="memalloc memdel strnew strdel strclr striter striteri strmap strmapi strequ strnequ strsub strjoin strtrim strsplit itoa putchar putstr putendl putnbr putchar_fd putstr_fd putendl_fd putnbr_fd"
bonus="lstnew lstdelone lstdel lstadd lstiter lstmap"

print_header()
{
	printf "${BOLD}$1:$NC\n"
}

check_files()
{
	error=0
	for i in $1; do
		file="ft_$i.c"
		if [ ! -f $file ]; then
			echo "missing: $file"
			(( error+=1 ))
		fi
	done
	[ $error -eq 0 ] && echo "ok"
}

print_header "fichier auteur"
cat -e auteur

print_header "norminette"
norminette *.[ch] | grep -E "Error|Warning" || echo "done"

print_header "check for libc"
check_files $libc

print_header "check for mandatory functions"
check_files $supp

print_header "check for bonus"
check_files $bonus

print_header "check for other functions"
files=$(echo "$libc $supp $bonus" | sed -e 's/^/ft_/' -e 's/$/.c/' -e 's/ /.c ft_/g')
for i in *.c; do
	case "$files" in
		*$i*) ;;
		*) echo $i;;
	esac
done
print_header "check for prototypes"
files=$(echo "$libc $supp $bonus" | sed -e 's/^/ft_/' -e 's/ / ft_/g')
for i in $files; do
	grep -q $i libft.h
	if [[ $? -ne 0 ]]; then
		echo "missing: $i"
	fi
done
