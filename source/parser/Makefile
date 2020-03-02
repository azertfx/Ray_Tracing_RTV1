# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hastid <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/03/01 01:27:28 by hastid            #+#    #+#              #
#    Updated: 2020/03/01 01:30:39 by hastid           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = parser.a

SRC_NAME =	child.c \
			utils.c \
			valid.c \
			parser.c \
			parent.c \
			child_utils.c \
			get_next_line.c

OBJ_NAME =	$(SRC_NAME:.c=.o)

SRC_PATH =	src
OBJ_PATH =	obj

SRC = $(addprefix $(SRC_PATH)/, $(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH)/, $(OBJ_NAME))

CFLAGS = -Wall -Werror -Wextra

Include = -I inc -I ../../include -I ../../libft/inc

DEPS = inc/parser.h

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
	@gcc  $(CFLAGS) $(Include) -o $@ -c $<

clean:
	@echo "\033[1;34mRemoving parser's objects directory\033[0m"
	@/bin/rm -rf $(OBJ_PATH) 2> /dev/null

fclean: clean
	@echo "\033[1;34mRemovimg $(NAME)\033[0m"
	@/bin/rm -f $(NAME)

re: fclean all
