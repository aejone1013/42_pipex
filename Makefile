# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaoh <jaoh@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/11 13:17:28 by jaoh              #+#    #+#              #
#    Updated: 2024/08/29 17:50:06 by jaoh             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Color Aliases
DEFAULT = \033[0;39m
GRAY = \033[0;90m
RED = \033[0;91m
GREEN = \033[0;92m
YELLOW = \033[0;93m
BLUE = \033[0;94m
MAGENTA = \033[0;95m
CYAN = \033[0;96m
WHITE = \033[0;97m
RESET = \033[0m

NAME 		= pipex

SRC			= pipex \
				pipex_utils \
				main
				
SRCS 		= $(addprefix srcs/, $(addsuffix .c, $(SRC)))

OBJS		= $(SRCS:.c=.o)

B_SRC		= pipex_bonus \
				pipex_utils_bonus \
				main_bonus

B_SRCS		= $(addprefix bonus/, $(addsuffix .c, $(B_SRC)))

B_OBJS		= $(B_SRCS:.c=.o)

CC			= gcc

CFLAGS		= -Wall -Wextra -Werror

LIBFT_PATH	= libft/
LIBFT		= $(LIBFT_PATH)libft.a

VALGRIND		= @valgrind --leak-check=full --show-leak-kinds=all \
--track-origins=yes --quiet --tool=memcheck --keep-debuginfo=yes

all: $(NAME)

$(NAME): $(OBJS)
	@make -C $(LIBFT_PATH)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)
	@echo "$(NAME): $(GREEN)$(NAME) is up to date!$(RESET)\n"

bonus: $(B_OBJS)
	@make -C $(LIBFT_PATH)
	@$(CC) $(CFLAGS) $(B_OBJS) $(LIBFT) -o $(NAME)
	@echo "Bonus $(NAME): $(GREEN)$(NAME) is up to date!$(RESET)\n"

%.o: %.c
	@$(CC) $(CFLAGS) -I$(LIBFT_PATH) -c $< -o $@

clean :
	@echo "$(CYAN)Cleaning up object files...$(DEFAULT)\n"
	@rm -f $(OBJS)
	@rm -f $(B_OBJS)
	@make fclean -C $(LIBFT_PATH)

fclean : clean
	@rm -f $(NAME)
	@echo "$(CYAN)Removed $(NAME)$(DEFAULT)\n"

re : fclean all

.PHONY : all bonus clean fclean re
