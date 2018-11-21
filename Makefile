# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jkettani <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/08 14:15:50 by jkettani          #+#    #+#              #
#    Updated: 2018/11/21 12:43:14 by jkettani         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all, clean, fclean, re

NAME = libft.a

SRC_PATH = .

INCLUDE_PATH = .

DEP_PATH = .deps

DEPFLAGS = -MT $@ -MMD -MP -MF $(DEP_PATH)/$*.Td

POSTCOMPILE = @mv -f $(DEP_PATH)/$*.Td $(DEP_PATH)/$*.d && touch $@

OBJ_PATH = obj

SRC_NAME = 	ft_bzero.c \
			ft_init_string.c \
			ft_memcpy.c \
			ft_memccpy.c \
			ft_memset.c \
			ft_print_char.c \
			ft_print_bytes.c \
			ft_putchar.c \
			ft_putchar_fd.c \
			ft_putendl.c \
			ft_putnbr.c \
			ft_putnbr_fd.c \
			ft_putstr.c \
			ft_putstr_fd.c \
			ft_putnbr_base.c \
			ft_strcat.c \
			ft_strchr.c \
			ft_strrchr.c \
			ft_strlcat.c \
			ft_strncat.c \
			ft_strcpy.c \
			ft_strncpy.c \
			ft_strdup.c \
			ft_strlen.c \
			ft_strstr.c

SRC = $(addprefix $(SRC_PATH)/,$(SRC_NAME))

OBJ = $(patsubst $(SRC_PATH)/%.c, $(OBJ_PATH)/%.o, $(SRC))

DEPS = $(patsubst $(SRC_PATH)/%.c, $(DEP_PATH)/%.d, $(SRC))

AR = ar

ARFLAGS = -rc

CC = gcc

CFLAGS = -Werror -Wall -Wextra

CPPFLAGS = -I$(INCLUDE_PATH)

COMPILE.c = $(CC) $(CFLAGS) $(CPPFLAGS) $(DEPFLAGS) -c

RM = rm -f

all: $(NAME)

$(NAME): $(OBJ)
	$(AR) $(ARFLAGS) $@ $?
	ranlib $@

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c $(DEP_PATH)/%.d | $(OBJ_PATH) $(DEP_PATH)
	$(COMPILE.c) $< -o $@ 
	$(POSTCOMPILE)

$(DEP_PATH)/%.d: ;

.PRECIOUS: $(DEP_PATH)/%.d

$(OBJ_PATH):
	mkdir $@

$(DEP_PATH):
	mkdir $@

clean:
	$(RM) $(OBJ)
	@rmdir $(OBJ_PATH) 2> /dev/null || true
	$(RM) $(DEPS)
	@rmdir $(DEP_PATH) 2> /dev/null || true

fclean: clean
	$(RM) $(NAME)

re: fclean all

include $(wildcard $(DEPS)) 
