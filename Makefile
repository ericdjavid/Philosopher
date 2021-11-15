# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tallaire <tallaire@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/27 18:14:57 by tallaire          #+#    #+#              #
#    Updated: 2021/05/27 18:15:03 by tallaire         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Colors
C_GREY		=	\e[1;30m
C_RED		=	\e[1;31m
C_GREEN		=	\e[1;32m
C_YELLOW	=	\e[1;33m
C_BLUE		=	\e[1;34m
C_PURPLE	=	\e[1;35m
C_CYAN		=	\e[1;36m
C_WHITE		=	\e[1;37m
C_END		=	\e[0m

NAME = philo
FLAGS = -Wall -Wextra -Werror
SRC =   ft_philosopher.c          \
		ft_init.c				  	  \
		ft_utils.c					  \
		ft_free_all.c			  \
		ft_process.c				\

all: $(NAME)

$(NAME):
	gcc -g -fsanitize=thread $(FLAGS) -o $(NAME) $(SRC) 
	@echo "$<[$(C_PURPLE)COMPILING$(C_END)]"
	@echo "$<[$(C_GREEN)OK$(C_END)]"

skiperror:
	@echo "$<[$(C_CYAN)Compiling skipping errors$(C_END)]"
	@gcc -g -pthread -ggdb -D_REENTRANT -o $(NAME) $(SRC)
	@echo "$<[$(C_GREEN)OK$(C_END)]"

clean:
	@rm -rf *.o
	@echo "$<[$(C_YELLOW)Cleaning .o files$(C_END)]"

fclean: clean
	@rm -rf $(NAME)

re: fclean all

reskiperror: fclean skiperror

.PHONY: all skiperror clean fclean re
