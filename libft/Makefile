#
#**************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anabaoui <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/10/08 15:15:18 by anabaoui          #+#    #+#              #
#    Updated: 2018/10/20 16:37:20 by anabaoui         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRC_NAME = ft_lstmap.c ft_putstr_fd.c ft_strncmp.c \
	ft_lstnew.c ft_strcat.c ft_strncpy.c \
	first_spaces.c ft_memalloc.c ft_strchr.c \
	ft_strnequ.c ft_atoi.c ft_memccpy.c \
	ft_strclr.c ft_strnew.c ft_bzero.c \
	ft_memchr.c ft_strcmp.c ft_strnstr.c \
	ft_count_chars.c ft_memcmp.c ft_strcpy.c \
	ft_strrchr.c ft_count_words.c ft_memcpy.c \
	ft_strdel.c ft_strsplit.c ft_isalnum.c \
	ft_memdel.c ft_strdup.c ft_strstr.c \
	ft_isalpha.c ft_memmove.c ft_strequ.c \
	ft_strsub.c ft_isascii.c ft_memset.c \
	ft_striter.c ft_strtrim.c ft_isdigit.c \
	ft_putchar.c ft_striteri.c ft_tolower.c \
	ft_isprint.c ft_putchar_fd.c ft_strjoin.c \
	ft_toupper.c ft_itoa.c ft_putendl.c \
	ft_strlcat.c last_spaces.c ft_lstadd.c \
	ft_putendl_fd.c ft_strlen.c ft_lstdel.c \
	ft_putnbr.c ft_strmap.c nbr_len.c \
	ft_lstdelone.c ft_putnbr_fd.c ft_strmapi.c \
	strtolower.c ft_lstiter.c ft_putstr.c ft_strncat.c \
	nbrtoabs.c nbrpower.c get_next_line.c ft_atof.c \
	ft_str_to_dbl.c ft_sign.c ft_is_number.c ft_strmequ.c ft_skip_chars.c 

OBJ_NAME =	$(SRC_NAME:.c=.o)

SRC_PATH =	src
OBJ_PATH =	obj

SRC = $(addprefix $(SRC_PATH)/, $(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH)/, $(OBJ_NAME))

CC = gcc -Wall -Wextra -Werror

INC = -I inc

DEPS = inc/libft.h

all: $(NAME)

$(NAME): $(OBJ)
	@clear
	@echo "\033[1;34mCreating $(NAME)\033[0m"
	@ar rc $@ $^
	@ranlib $@

$(OBJ_PATH)/%.o : $(SRC_PATH)/%.c $(DEPS)
	@clear
	@mkdir $(OBJ_PATH) 2>/dev/null || true
	@echo "Compiling \033[1;33m[$<]\033[0m to \033[1;32m[$@]\033[0m"
	@$(CC) $(INC) -o $@ -c $<
	
clean:
	@echo "\033[1;34mRemoving libft's objects directory\033[0m"
	@/bin/rm -rf $(OBJ_PATH) 2> /dev/null

fclean: clean
	@echo "\033[1;34mRemovimg $(NAME)\033[0m"
	@/bin/rm -f $(NAME)

re: fclean all
