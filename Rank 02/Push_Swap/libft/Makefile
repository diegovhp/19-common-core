# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dvan-hem <dvan-hem@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/05 14:56:28 by dvan-hem          #+#    #+#              #
#    Updated: 2025/04/04 18:10:58 by dvan-hem         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC				= cc
RM				= rm -f
CFLAGS			= -Wall -Wextra -Werror -I. -fPIC

NAME			= libft.a

SRCS			=	ft_isalnum.c ft_isprint.c ft_memcmp.c ft_putchar_fd.c ft_itoa.c ft_strrchr.c \
					ft_strlcat.c ft_strncmp.c ft_atoi.c ft_isalpha.c ft_split.c ft_strnstr.c \
					ft_memcpy.c  ft_strchr.c  ft_strlcpy.c ft_putendl_fd.c ft_striteri.c \
					ft_tolower.c ft_bzero.c   ft_isascii.c ft_putnbr_fd.c ft_strjoin.c ft_strtrim.c \
					ft_memmove.c ft_strdup.c  ft_strlen.c  ft_putstr_fd.c ft_strmapi.c ft_substr.c \
					ft_toupper.c ft_calloc.c  ft_isdigit.c ft_memchr.c  ft_memset.c \
					ft_printf/ft_printf.c ft_printf/ft_format.c ft_printf/ft_putchar.c \
       				ft_printf/ft_putstr.c ft_printf/ft_putnbr.c ft_printf/ft_puthex.c ft_printf/ft_putptr.c \
					get_next_line/get_next_line.c get_next_line/get_next_line_utils.c
					
OBJS			= $(SRCS:.c=.o)

all:			$(NAME)

$(NAME):		$(OBJS)
				ar rcs $(NAME) $(OBJS)

clean:
				$(RM) $(OBJS)

fclean:			clean
				$(RM) $(NAME)

re:				fclean $(NAME)

.PHONY:			all clean fclean re 