# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anabaoui <anabaoui@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/06 03:38:58 by anabaoui          #+#    #+#              #
#    Updated: 2020/02/29 02:55:13 by anabaoui         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = rtv1

SRC_NAME = main.c rtv1.c intersection.c keys_hook.c\
			objects.c vectors1.c vectors2.c vectors3.c pixel_color.c camera.c\
			guide_btn.c instruction.c

OBJ_NAME =	$(SRC_NAME:.c=.o)

SRC_PATH =	source
OBJ_PATH =	objet

SRC = $(addprefix $(SRC_PATH)/, $(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH)/, $(OBJ_NAME))

CC = gcc -Wall -Wextra -Werror

LIB =  libft/libft.a \
	   source/parser/parser.a \
	   -lmlx -framework OpenGL -framework AppKit
		
DEPS = include/rtv1.h

INC = -Iinclude -Ilibft/inc -Isource/parser/inc

all : $(NAME)

$(NAME) : $(OBJ) lib_ft par_ft
	@clear
	@echo "	\033[1;34mCreating RT"
	@$(CC) $(OBJ) $(LIB)  -o $@

lib_ft :
	@make -C libft

par_ft :
	@make -C source/parser

$(OBJ_PATH)/%.o : $(SRC_PATH)/%.c $(DEPS)
	@clear
	@mkdir $(OBJ_PATH) 2> /dev/null || true
	@$(CC) $(INC) -o $@ -c $< 
	@echo "Compiling \033[1;36m[$<]\033[0m to \033[1;32m[$@]\033[0m"

clean :
	@make clean -C libft
	@make clean -C source/parser
	@echo "\033[1;33mRemoving $(NAME)'s objects directory\033[0m"
	@rm -rf $(OBJ_PATH) 2> /dev/null

fclean : clean
	@make fclean -C libft
	@make fclean -C source/parser
	@echo "\033[1;33mRemoving $(NAME)\033[0m"
	@rm -rf $(NAME)

re : fclean all