# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jkettani <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/08 14:15:50 by jkettani          #+#    #+#              #
#    Updated: 2018/12/14 17:57:02 by jkettani         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME =          libft.a
SRC_PATH =      srcs
INCLUDE_PATH =  includes
OBJ_PATH =      obj
DEP_PATH =      .deps
RM =            rm -rf
AR =            ar
ARFLAGS =       -rcs
CC =            gcc
CFLAGS =        -Werror -Wall -Wextra
CPPFLAGS =      -I$(INCLUDE_PATH)
COMPILE.c =     $(CC) $(CFLAGS) $(CPPFLAGS) $(DEPFLAGS) -c
DEPFLAGS =      -MT $@ -MMD -MP -MF $(OBJ_PATH)/$*.Td
POSTCOMPILE =   @mv -f $(OBJ_PATH)/$*.Td $(OBJ_PATH)/$*.d && touch $@
SRC_CHAR =      ft_isalnum ft_isalpha ft_isascii ft_isblank ft_iscntrl \
			    ft_isdigit ft_isgraph ft_islower ft_isprint ft_isspace \
			    ft_isupper ft_isxdigit ft_tolower ft_toupper
SRC_CONVERT =   ft_atoi ft_itoa ft_itoa_base
SRC_LIST =      ft_lstadd ft_lstdel ft_lstdelone ft_lstiter ft_lstmap \
				ft_lstnew
SRC_MEM =       ft_bzero ft_memalloc ft_memchr ft_memcmp ft_memcpy \
				ft_memccpy ft_memdel ft_memmove ft_memset
SRC_PRINT =     ft_print_bytes ft_putchar ft_putchar_fd ft_putendl \
			    ft_putendl_fd ft_putnbr ft_putnbr_base ft_putnbr_fd \
			    ft_putstr ft_putstr_fd
SRC_STR =       ft_count_words_c ft_strcat ft_strchr ft_strclr ft_strcmp \
		        ft_strcpy ft_strdel ft_strdup ft_strdup_c ft_strequ \
		        ft_striter ft_striteri ft_strjoin ft_strlcat ft_strlen \
		        ft_strmap ft_strmapi ft_strncat ft_strncmp ft_strncpy \
		        ft_strnequ ft_strnew ft_strnstr ft_strrchr ft_strsplit \
		        ft_strstr ft_strsub ft_strtrim
SRC_NAME =      $(addprefix char/, $(SRC_CHAR)) \
				$(addprefix convert/, $(SRC_CONVERT)) \
				$(addprefix list/, $(SRC_LIST)) \
				$(addprefix mem/, $(SRC_MEM)) \
				$(addprefix print/, $(SRC_PRINT)) \
				$(addprefix str/, $(SRC_STR))
SRC =           $(addprefix $(SRC_PATH)/, $(addsuffix .c, $(SRC_NAME)))
OBJ =           $(patsubst %.c, $(OBJ_PATH)/%.o, $(SRC))
DEP =           $(patsubst %.c, $(OBJ_PATH)/%.d, $(SRC))

.PHONY: all
all: $(NAME)

$(NAME): $(OBJ)
	$(AR) $(ARFLAGS) $@ $?

$(OBJ): $(OBJ_PATH)/%.o: %.c
	$(COMPILE.c) $< -o $@ 
	$(POSTCOMPILE)

$(OBJ_PATH)/%.d: ;

$(OBJ_PATH)/%:
	mkdir -p $@

.PHONY: clean
clean:
	$(RM) $(OBJ_PATH)

.PHONY: fclean
fclean: clean
	$(RM) $(NAME)

.PHONY: re
re: fclean all

$(foreach OBJECT,$(OBJ),$(eval $(OBJECT): | $(dir $(OBJECT))))

include $(wildcard $(DEP))
