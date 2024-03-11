# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cravegli <cravegli@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/08 12:45:03 by cravegli          #+#    #+#              #
#    Updated: 2024/03/11 14:51:48 by cravegli         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= pipex
INCLUDE			= pipex.h
LIBFT			= libft
CC				= gcc
CFLAGS			= -Wall -Werror -Wextra
DBUG			= -fsanitize=address
RM				= rm -rf



SRC			= main.c ft_error.c ft_process.c ft_free.c

OBJ			=$(SRC:.c=.o)

all:		$(NAME)

$(NAME):	$(OBJ)
			@make -C $(LIBFT)
			@$(CC) $(CFLAGS) $(OBJ) libft/libft.a -o $(NAME)

.c.o:
	$(CC) $(CFLAGS) -c -o $@ $< $(INCLUDES)

clean:
			@$(RM) $(OBJ)
			@make clean -C $(LIBFT)

fclean:		clean
			@$(RM) $(NAME)
			@$(RM) $(LIBFT)/libft.a

re:			fclean all

.PHONY:		all clean fclean re