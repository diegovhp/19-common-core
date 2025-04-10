# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dvan-hem <dvan-hem@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/28 18:12:32 by dvan-hem          #+#    #+#              #
#    Updated: 2025/04/04 17:40:45 by dvan-hem         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = so_long

SRC_DIR = srcs
OBJ_DIR = objs
INCLUDES = -Iincludes -Ilibft -Iminilibx-linux
LIBS = -Llibft -lft -Lminilibx-linux -lmlx -lXext -lX11 -lm

SRCS = $(shell find $(SRC_DIR) -name "*.c")
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

CC = gcc
CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJS)
	@make -C libft
	@make -C minilibx-linux
	@$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@make clean -C libft
	@rm -rf $(OBJ_DIR)

fclean: clean
	@make fclean -C libft
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re