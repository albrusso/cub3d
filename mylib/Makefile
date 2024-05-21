# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: albrusso <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/07 14:16:03 by albrusso          #+#    #+#              #
#    Updated: 2024/03/19 16:20:46 by albrusso         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

################################################################################
#                                  CONFIG                                      #
################################################################################

NAME	=	libftprintfgnl.a
CC		=	gcc
CFLAGS	=	-Wall -Wextra -g
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
SRC		=	libft/ft_isalnum.c         \
			libft/ft_isprint.c         \
			libft/ft_memcmp.c          \
			libft/ft_putchar_fd.c      \
			libft/ft_split.c           \
			libft/ft_strlcat.c         \
			libft/ft_strncmp.c         \
			libft/ft_substr.c          \
			libft/ft_atoi.c            \
			libft/ft_isalpha.c         \
			libft/ft_itoa.c            \
			libft/ft_memcpy.c          \
			libft/ft_putendl_fd.c      \
			libft/ft_strchr.c          \
			libft/ft_strlcpy.c         \
			libft/ft_strnstr.c         \
			libft/ft_tolower.c         \
			libft/ft_bzero.c           \
			libft/ft_isascii.c         \
			libft/ft_memmove.c         \
			libft/ft_putnbr_fd.c       \
			libft/ft_strdup.c          \
			libft/ft_strlen.c          \
			libft/ft_strrchr.c         \
			libft/ft_toupper.c         \
			libft/ft_calloc.c          \
			libft/ft_isdigit.c         \
			libft/ft_memchr.c          \
			libft/ft_memset.c          \
			libft/ft_putstr_fd.c       \
			libft/ft_strjoin.c         \
			libft/ft_strmapi.c         \
			libft/ft_strtrim.c         \
			libft/ft_striteri.c        \
			libft/ft_lstadd_back.c     \
			libft/ft_lstadd_front.c    \
			libft/ft_lstclear.c        \
			libft/ft_lstdelone.c       \
			libft/ft_lstiter.c         \
			libft/ft_lstlast.c         \
			libft/ft_lstnew.c          \
			libft/ft_lstsize.c         \
			ft_printf/ft_printf.c      \
			ft_printf/ft_char.c        \
			ft_printf/ft_int.c         \
			ft_printf/ft_pointer.c     \
			ft_printf/ft_string.c      \
			ft_printf/ft_unsigned.c    \
			ft_printf/ft_hexadecimal.c \
			gnl/get_next_line.c        \
			gnl/get_next_line_utils.c

OBJ	=	$(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

################################################################################
#                                   MAKE                                       #
################################################################################

all:	$(NAME)
$(NAME): $(OBJ)
	@ar rcs $@ $^

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	@printf "$(WHITE)%s$(BLUE)%-$(SIZE)s$(GREEN)%s$(DEFAULT)\n" "Compiling... " "$<" "[OK]"
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)/libft
	@mkdir -p $(OBJ_DIR)/ft_printf
	@mkdir -p $(OBJ_DIR)/gnl

clean:
	@for file in $(OBJ); do \
		printf "$(WHITE)%s$(YELLOW)%-$(SIZE)s$(GREEN)%s$(DEFAULT)\n" "Removing...  " "$$file" "[OK]"; \
	done
	@rm -f $(OBJ)
	@rm -rf $(OBJ_DIR)

fclean: clean
	@printf "$(WHITE)%s$(RED)%-$(SIZE)s$(GREEN)%s$(DEFAULT)\n" "Removing...  " "$(NAME)" "[OK]"
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
