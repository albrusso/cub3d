# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: albrusso <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/19 19:08:41 by albrusso          #+#    #+#              #
#    Updated: 2024/05/24 21:34:29 by albrusso         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

################################################################################
#                                  CONFIG                                      #
################################################################################

NAME	=	cub3d
CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror -g
MYLIB	=	./mylib/libftprintfgnl.a
MLXFLAGS	=	-L ./minilibx/ -lmlx -framework OpenGL -framework AppKit -lz
OBJ_DIR	=	.obj
SIZE	=	40

################################################################################
#                                  COLORS                                      #
################################################################################

RED		=	\033[1;31m
YELLOW	=	\033[1;33m
BLUE	=	\033[1;34m
GREEN	=	\033[1;32m
WHITE	=	\033[1;37m
DEFAULT	=	\033[0m

################################################################################
#                                   FILES                                      #
################################################################################

SRC		=	src/main.c \
			src/cleanup.c \
			src/handler.c \
			src/initialize.c \
			src/loop.c \
			src/map.c \
			src/raycasting.c \
			src/render.c \
			src/setup.c

OBJ		=	$(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

################################################################################
#                                   MAKE                                       #
################################################################################

ifeq ($(shell uname), Linux)
MLXFLAGS	=	minilibx/libmlx.a -lX11 -lXext -lm
endif

all:	$(NAME)
$(NAME): $(OBJ)
	@make -sC mylib
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(MYLIB) $(MLXFLAGS)

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	@printf "$(WHITE)%s$(BLUE)%-$(SIZE)s$(GREEN)%s$(DEFAULT)\n" "Compiling... " "$<" "[OK]"
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)/src
	@mkdir -p $(OBJ_DIR)/src/utils
	@mkdir -p $(OBJ_DIR)/src/parser

clean:
	@make clean -sC mylib
	@for file in $(OBJ); do \
		printf "$(WHITE)%s$(YELLOW)%-$(SIZE)s$(GREEN)%s$(DEFAULT)\n" "Removing...  " "$$file" "[OK]"; \
	done
	@rm -f $(OBJ)
	@rm -rf $(OBJ_DIR)

fclean: clean
	@printf "$(WHITE)%s$(RED)%-$(SIZE)s$(GREEN)%s$(DEFAULT)\n" "Removing...  " "libftprintfgnl" "[OK]"
	@printf "$(WHITE)%s$(RED)%-$(SIZE)s$(GREEN)%s$(DEFAULT)\n" "Removing...  " "$(NAME)" "[OK]"
	@rm -f $(MYLIB)
	@rm -f $(NAME)

re: fclean all

run: $(NAME)
	./$(NAME)

mem: $(NAME)
		valgrind --leak-check=full --show-leak-kinds=all ./$(NAME)

.PHONY: all clean fclean re run mem