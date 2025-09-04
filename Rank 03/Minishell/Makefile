# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tstevens <tstevens@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/16 13:45:38 by dvan-hem          #+#    #+#              #
#    Updated: 2025/08/23 17:14:54 by tstevens         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell

CC			= cc
CFLAGS		= -Werror -Wextra -Wall -gdwarf-4 -g
rm			= rm -f

LIBFT		= ./libft/libft.a
SRC_DIR		= sources/
OBJ_DIR 	= objects/
LIBFT_DIR 	= ./libft/
INC_DIR 	= includes/

INC			= -I $(INC_DIR) -I $(LIBFT_DIR)

SRCS		= 	$(SRC_DIR)main.c \
				$(SRC_DIR)base/init_data.c \
				$(SRC_DIR)base/free.c \
				$(SRC_DIR)builtins_cmds/export.c \
				$(SRC_DIR)builtins_cmds/unset.c \
				$(SRC_DIR)builtins_cmds/cd.c \
				$(SRC_DIR)builtins_cmds/env.c \
				$(SRC_DIR)builtins_cmds/pwd.c \
				$(SRC_DIR)builtins_cmds/echo.c \
				$(SRC_DIR)builtins_cmds/exit.c \
				$(SRC_DIR)environment/env_utils.c \
				$(SRC_DIR)environment/env_edit.c \
				$(SRC_DIR)environment/env_core.c \
				$(SRC_DIR)error/exit.c \
				$(SRC_DIR)error/error_management.c \
				$(SRC_DIR)exec/exec.c \
				$(SRC_DIR)exec/cmd_exec.c \
				$(SRC_DIR)exec/utils.c \
				$(SRC_DIR)exec/path_management.c \
				$(SRC_DIR)expansion/expand_var.c \
				$(SRC_DIR)expansion/expand_utils.c \
				$(SRC_DIR)expansion/var_finder.c \
				$(SRC_DIR)expansion/var_checker.c \
				$(SRC_DIR)expansion/handle_quotes.c \
				$(SRC_DIR)expansion/delete_quotes.c \
				$(SRC_DIR)expansion/value_recovery.c \
				$(SRC_DIR)expansion/replace_var.c \
				$(SRC_DIR)lexer/user_input_parsing.c \
				$(SRC_DIR)lexer/tokenize.c \
				$(SRC_DIR)lexer/tokenize_utils.c \
				$(SRC_DIR)lexer/var_checker.c \
				$(SRC_DIR)lexer/lexer_syntax.c \
				$(SRC_DIR)lexer/token_utils.c \
				$(SRC_DIR)lexer/token_utils_2.c \
				$(SRC_DIR)parsing/new_cmd.c \
				$(SRC_DIR)parsing/echo_args.c \
				$(SRC_DIR)parsing/echo_utils.c \
				$(SRC_DIR)parsing/default_args.c \
				$(SRC_DIR)parsing/parsing_core1.c \
				$(SRC_DIR)parsing/parsing_core2.c \
				$(SRC_DIR)parsing/parsing_core2_utils.c \
				$(SRC_DIR)parsing/parsing_core3.c \
				$(SRC_DIR)parsing/parsing_core4.c \
				$(SRC_DIR)parsing/cmd_list.c \
				$(SRC_DIR)parsing/free_cmd_list.c \
				$(SRC_DIR)system/pipes.c \
				$(SRC_DIR)system/file_io.c \
				$(SRC_DIR)system/signal.c \
				$(SRC_DIR)system/signal2.c 

OBJ 		= $(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(SRCS))

start:
					@make all --no-print-directory

$(LIBFT):
					@make -C $(LIBFT_DIR) --no-print-directory --silent

all: 				logo $(NAME)

logo:
	@tput civis
	@printf "\033[38;2;241;178;172m"; \
	for c in "W" "e" "l" "c" "o" "m" "e" " " "t" "o" " " "D" "i" "e" "g" "o" "'" "s" " " "&" " " "T" "o" "m" "'" "s"; do \
		printf "$$c"; \
		sleep 0.03; \
	done; \
	printf "\n\n"; \
	{ \
	echo "\033[38;2;162;156;187m		     :::       :::    :::    :::     :::    :::    ::::::::    :::    :::    :::::::::    :::         :::"; \
	echo "\033[38;2;125;120;163m	            :+::     :::+    :+:    :+::    :+:    :+:   :+:    :+:   :+:    :+:    :+:          :+:         :+:"; \
	echo "\033[38;2;162;156;187m	           +:+++  +++:++    +:+    +:+++   +:+    +:+   +:+          +:+    +:+    +:+          +:+         +:+"; \
	echo "\033[38;2;125;120;163m	          +#+  +++  #++    +#+    +#+ ++  +#+    +#+   #++:++#++    +#++:++#++    +#++:++#+    +#+         +#+"; \
	echo "\033[38;2;162;156;187m	         +#+       +#+    +#+    +#+  ++ +#+    +#+         +#+    +#+    +#+    +#+          +#+         +#+"; \
	echo "\033[38;2;125;120;163m	        #+#       #+#    #+#    #+#   ++#+#    #+#    #+#   #+#   #+#    #+#    #+#          #+#         #+#"; \
	echo "\033[38;2;162;156;187m	       ###       ###    ###    ###    +###    ###    ########    ###    ###    #########    ########    ########"; \
	} | while IFS= read -r line; do \
		printf "$$line\n"; \
		sleep 0.03; \
	done; \
	printf "\033[0m\n"; \
	tput cnorm

progress_bar:
	@tput civis
	@printf "\n\033[38;2;241;178;172m╭────────────────────────────────────────────╮\n"
	@printf " \033[38;2;241;178;172m│\033[38;2;125;120;163m"
	@i=0; \
	while [ $$i -le 40 ]; do \
		sleep 0.01; \
		printf "█"; \
		i=$$((i + 1)); \
	done; \
	printf "\033[38;2;241;178;172m│\n"; \
	printf "╰────────────────────────────────────────────╯\033[0m\n"; \
	tput cnorm


GLOSSY_GRAPE = \033[38;2;162;156;187m
RHYTHM       = \033[38;2;125;120;163m
MELON        = \033[38;2;241;178;172m
RESET        = \033[0m

$(NAME): $(OBJ) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -l readline -o $(NAME) $(INC)
	@$(MAKE) progress_bar --no-print-directory

$(OBJ_DIR)%.o:		$(SRC_DIR)%.c
					@mkdir -p $(@D)
					@$(CC) $(CFLAGS) -c $< -o $@ $(INC)

clean:
	@tput civis; \
	printf "\033[38;2;241;178;172m"; \
	for c in "🧹" " " "C" "l" "e" "a" "n" "i" "n" "g" " " "🧹"; do \
		printf "$$c"; \
		sleep 0.03; \
	done; \
	\
	printf "\n\n\033[38;2;241;178;172m╭────────────────────────────────────────────╮\n"; \
	printf " \033[38;2;241;178;172m│\033[38;2;125;120;163m"; \
	i=0; \
	while [ $$i -le 40 ]; do \
		sleep 0.01; \
		printf "█"; \
		i=$$((i + 1)); \
	done; \
	printf "\033[38;2;241;178;172m│\n"; \
	printf "╰────────────────────────────────────────────╯\033[0m\n"; \
	tput cnorm
	@$(RM) -r $(OBJ_DIR)
	@make clean -C ./libft --no-print-directory > /dev/null

fclean:
	@tput civis; \
	printf "\033[38;2;241;178;172m"; \
	for c in "🧹" " " "F" "u" "l" "l" "y" " " "c" "l" "e" "a" "n" "i" "n" "g" " " "🧹"; do \
		printf "$$c"; \
		sleep 0.03; \
	done; \
	\
	printf "\n\n\033[38;2;241;178;172m╭────────────────────────────────────────────╮\n"; \
	printf " \033[38;2;241;178;172m│\033[38;2;125;120;163m"; \
	i=0; \
	while [ $$i -le 40 ]; do \
		sleep 0.01; \
		printf "█"; \
		i=$$((i + 1)); \
	done; \
	printf "\033[38;2;241;178;172m│\n"; \
	printf "╰────────────────────────────────────────────╯\033[0m\n"; \
	printf "\n\n\033[38;2;241;178;172m"; \
	for c in "✅" " " "D" "o" "n" "e" " " "✅"; do \
		printf "$$c"; \
		sleep 0.03; \
	done; \
	printf "\n"; \
	tput cnorm
	@$(RM) -r $(OBJ_DIR)
	@$(RM) $(NAME)
	@$(RM) $(LIBFT)
	@make fclean -C ./libft --no-print-directory > /dev/null

re:
	@tput civis; \
	printf "\033[38;2;241;178;172m"; \
	for c in "🔁" " " "R" "e" "-" "M" "a" "k" "i" "n" "g" "." "." "."; do \
		printf "$$c"; \
		sleep 0.03; \
	done; \
	\
	printf "\n\n\033[38;2;241;178;172m╭────────────────────────────────────────────╮\n"; \
	printf " \033[38;2;241;178;172m│\033[38;2;125;120;163m"; \
	i=0; \
	while [ $$i -le 40 ]; do \
		sleep 0.01; \
		printf "█"; \
		i=$$((i + 1)); \
	done; \
	printf "\033[38;2;241;178;172m│\n"; \
	printf "╰────────────────────────────────────────────╯\033[0m\n"; \
	tput cnorm
	@$(MAKE) fclean --no-print-directory
	@$(MAKE) all --no-print-directory

.PHONY: start all re clean fclean logo
