# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaoh <jaoh@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/11 13:17:28 by jaoh              #+#    #+#              #
#    Updated: 2024/10/15 15:38:55 by jaoh             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Colors constants
PURPLE			= \033[38;5;141m
GREEN			= \033[38;5;46m
RED				= \033[0;31m
GREY			= \033[38;5;240m
RESET			= \033[0m
BOLD			= \033[1m
CLEAR			= \r\033[K

NAME 		= pipex

SRC_FILE	= pipex \
				pipex_utils \
				main
				
SRCS 		= $(addprefix srcs/, $(addsuffix .c, $(SRC_FILE)))

OBJS		= $(SRCS:.c=.o)

B_SRC_FILE		=

B_SRCS		= $(addprefix bonus/, $(addsuffix .c, $(B_SRC_FILE)))

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
	@printf "${CLEAR}${RESET}${GREY}────────────────────────────────────────────────────────────────────────────\n${RESET}${GREEN}»${RESET} [${PURPLE}${BOLD}${B_NAME}${RESET}]: ${RED}${BOLD}${B_NAME} ${RESET}compiled ${GREEN}successfully${RESET}.${GREY}\n${RESET}${GREY}────────────────────────────────────────────────────────────────────────────\n${RESET}"


bonus: $(B_OBJS)
	@make -C $(LIBFT_PATH)
	@$(CC) $(CFLAGS) $(B_OBJS) $(LIBFT) -o $(NAME)
	@printf "${CLEAR}${RESET}${GREEN}»${RESET} [${PURPLE}${BOLD}${NAME}${RESET}]: Objects were cleaned ${GREEN}successfully${RESET}.\n${RESET}"

%.o: %.c
	@$(CC) $(CFLAGS) -I$(LIBFT_PATH) -c $< -o $@

clean :
	@rm -f $(OBJS) $(B_OBJS)
	@make fclean -C $(LIBFT_PATH)
	@printf "${CLEAR}${RESET}${GREEN}»${RESET} [${PURPLE}${BOLD}${NAME}${RESET}]: Objects were cleaned ${GREEN}successfully${RESET}.\n${RESET}"

fclean : clean
	@rm -f $(NAME) $(B_NAME)
	@printf "${CLEAR}${RESET}${GREY}────────────────────────────────────────────────────────────────────────────\n${RESET}${GREEN}»${RESET} [${PURPLE}${BOLD}${NAME}${RESET}]: Project cleaned ${GREEN}successfully${RESET}.${GREY}\n${RESET}${GREY}────────────────────────────────────────────────────────────────────────────\n${RESET}"

re : fclean all

.PHONY : all bonus clean fclean re
