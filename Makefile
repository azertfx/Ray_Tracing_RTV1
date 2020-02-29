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

INC = srcs/rtv1.h

SRC_PATH = srcs

SRC_NAME = main.c rtv1.c parse_file.c parse_property.c intersection.c keys_hook.c\
			objects.c vectors1.c vectors2.c vectors3.c pixel_color.c camera.c\
			guide_btn.c instruction.c

SRC = $(addprefix $(SRC_PATH)/,$(SRC_NAME))

OBJ = $(SRC:.c=.o)

CC = gcc -Wall -Wextra -Werror

LIB = -L ./libft -lft -L ./miniLibX -lmlx -framework OpenGL -framework AppKit

all : lib_ft $(NAME)

$(NAME) : $(OBJ) $(INC)
	@$(CC) $(LIB) $(OBJ) -o $(NAME)
	@echo "\033[1;32mRtv1 binary created\033[0m"

lib_ft :
	make -C libft

$(SRC_PATH)/%.o : $(SRC_PATH)/%.c $(INC)
	@$(CC) -c $< -o $@
	@echo "Rtv1 : $< \033[1;32mDone\033[0m"

clean :
	@make clean -C libft
	@rm -rf $(OBJ)

fclean : clean
	@make fclean -C libft
	@rm -rf $(NAME)

re : fclean all