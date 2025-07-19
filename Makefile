# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmutsulk <mmutsulk@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/27 12:01:55 by mmutsulk          #+#    #+#              #
#    Updated: 2025/07/16 15:59:16 by mmutsulk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC				=	main.c init_data.c utils.c routine.c monitoring.c

OBJ 			=	$(SRC:.c=.o)

CC				= cc
RM				= rm -f
CFLAGS			= -Wall -Wextra -Werror
NAME			= philo

GREEN			= \033[1;32m
RESET			= \033[0m

all:			$(NAME)

%.o: %.c
				$(CC) -o $@ -c $< $(CFLAGS)

$(NAME):		$(OBJ)
				@$(CC) $(CFLAGS) -o $(NAME) $(OBJ)
				@echo "$(GREEN)"
				@echo "▗▄▄▖ ▗▖ ▗▖▗▄▄▄▖▗▖    ▗▄▖     ▗▄▄▖ ▗▄▄▄▖ ▗▄▖ ▗▄▄▄ ▗▖  ▗▖"
				@echo "▐▌ ▐▌▐▌ ▐▌  █  ▐▌   ▐▌ ▐▌    ▐▌ ▐▌▐▌   ▐▌ ▐▌▐▌  █ ▝▚▞▘"
				@echo "▐▛▀▘ ▐▛▀▜▌  █  ▐▌   ▐▌ ▐▌    ▐▛▀▚▖▐▛▀▀▘▐▛▀▜▌▐▌  █  ▐▌"
				@echo "▐▌   ▐▌ ▐▌▗▄█▄▖▐▙▄▄▖▝▚▄▞▘    ▐▌ ▐▌▐▙▄▄▖▐▌ ▐▌▐▙▄▄▀  ▐▌"
				@echo "$(RESET)"
clean:
				$(RM) $(OBJ)

fclean:			clean
				$(RM) $(NAME)

re:				fclean $(NAME)

.PHONY:			all clean fclean re
