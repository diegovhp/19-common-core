# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dvan-hem <dvan-hem@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/17 15:04:51 by dvan-hem          #+#    #+#              #
#    Updated: 2025/03/25 10:59:57 by dvan-hem         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g

SRCS = srcs/pipex.c srcs/utils.c 
OBJS = $(SRCS:.c=.o)
HEADER = -Iincludes

all: $(NAME)

$(NAME): $(OBJS)
	@make re -C ./libft
	@$(CC) $(OBJS) -Llibft -lft -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(HEADER) -c $< -o $@

clean:
	@make clean -C ./libft
	rm -f $(OBJS)

fclean: clean
	@make fclean -C ./libft
	@rm -f $(NAME)

re: fclean all

.PHONY: 	all clean fclean re