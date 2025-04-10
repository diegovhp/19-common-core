# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dvan-hem <dvan-hem@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/18 13:48:48 by dvan-hem          #+#    #+#              #
#    Updated: 2024/11/19 17:09:31 by dvan-hem         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			= cc
RM			= rm -f
CFLAGS		= -Wall -Wextra -Werror -I.

NAME		= libftprintf.a

SRCS		= ft_printf.c ft_putnbr.c ft_putstr.c ft_putchar.c ft_puthex.c \
			  ft_format.c ft_putptr.c
				

OBJS 		= $(SRCS:.c=.o)

all: 		$(NAME)

$(NAME): 	$(OBJS)
			ar rcs $(NAME) $(OBJS)

clean:
			$(RM) $(OBJS)

fclean: 	clean
			$(RM) $(NAME)

re: 		fclean $(NAME)

.PHONY: 	all clean fclean re
