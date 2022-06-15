# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jheiskan <jheiskan@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/14 14:17:22 by nsamoilo          #+#    #+#              #
#    Updated: 2022/06/15 13:41:06 by jheiskan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lem-in
FLAGS = -Wall -Wextra -Werror

INCL = -Iincludes/ -I$(LIB_DIR)/includes

SRCS =	main.c array_manipulation.c

OBJ_NAME = $(SRCS:.c=.o)

OBJ = $(addprefix $(OBJ_DIR),$(OBJ_NAME))
SRC_DIR = srcs/
OBJ_DIR = objs/
LIB_DIR = libft/

all: $(NAME)

debug: FLAGS += -g
debug: re
no_flags: FLAGS = -w -g
no_flags: re

$(NAME): $(OBJ)
	@make -C $(LIB_DIR) --silent
	@gcc $(FLAGS) -o $(NAME) $(OBJ) -L $(LIB_DIR) -lft
	@echo "Compiled Lem-in"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@gcc $(FLAGS) -o $@ -c $< $(INCL)

clean:
	@make clean -C $(LIB_DIR) --silent
	@rm -f $(OBJ)
	@echo "Removed object files"

fclean: clean
	@rm -f $(NAME)
	@make fclean -C $(LIB_DIR) --silent
	@echo "Removed executables"

re: fclean all

rm_all:
	@rm $(LIB_DIR)*.o
	@rm $(LIB_DIR)*.a
	@rm -rf ./objs
	@rm -f lem-in*
	@echo "Removed all exes and objects"

.PHONY: all clean fclean re
