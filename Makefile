# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaoh <jaoh@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/29 11:05:30 by jaoh              #+#    #+#              #
#    Updated: 2024/10/29 12:36:21 by jaoh             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

PURPLE			= \033[38;5;141m
GREEN			= \033[38;5;46m
RED				= \033[0;31m
GREY			= \033[38;5;240m
RESET			= \033[0m
BOLD			= \033[1m
CLEAR			= \r\033[K

NAME			= pipex
B_NAME			= pipex_bonus

SRC_FILE		= pipex \
					pipex_error \
					pipex_exec \
					pipex_unix

SRCS 			= $(addprefix srcs/, $(addsuffix .c, $(SRC_FILE)))

OBJS			= $(SRCS:.c=.o)

B_SRC_FILE		=	pipex_bonus \
					pipex_error_bonus \
					pipex_exec_bonus \
					pipex_unix_bonus

B_SRCS			= $(addprefix bonus/, $(addsuffix .c, $(B_SRC_FILE)))

B_OBJS			= $(B_SRCS:.c=.o)

CC				= gcc

CFLAGS			= -Wall -Wextra -Werror

LIBFT_PATH		= libft/
LIBFT			= $(LIBFT_PATH)libft.a

all: 			$(NAME)

$(NAME): $(OBJS)
	@make -C $(LIBFT_PATH)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)
	@printf "${CLEAR}${RESET}${GREY}────────────────────────────────────────────────────────────────────────────\n${RESET}${GREEN}»${RESET} [${PURPLE}${BOLD}${NAME}${RESET}]: ${RED}${BOLD}${NAME} ${RESET}compiled ${GREEN}successfully${RESET}.${GREY}\n${RESET}${GREY}────────────────────────────────────────────────────────────────────────────\n${RESET}"

bonus : $(B_NAME)

$(B_NAME) : $(B_OBJS)
	@make -C $(LIBFT_PATH)
	@$(CC) $(CFLAGS) $(B_OBJS) $(LIBFT) -o $(B_NAME)
	@printf "${CLEAR}${RESET}${GREY}────────────────────────────────────────────────────────────────────────────\n${RESET}${GREEN}»${RESET} [${PURPLE}${BOLD}${B_NAME}${RESET}]: ${RED}${BOLD}${B_NAME} ${RESET}compiled ${GREEN}successfully${RESET}.${GREY}\n${RESET}${GREY}────────────────────────────────────────────────────────────────────────────\n${RESET}"

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

rebonus : fclean bonus

.PHONY : all bonus clean fclean re rebonus