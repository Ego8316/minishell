# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ego <ego@student.42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/27 21:17:01 by pkurt             #+#    #+#              #
#    Updated: 2025/05/05 19:35:45 by ego              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = gcc
FLAGS = -Wall -Wextra -Werror -fsanitize=address
LIBFT = -L libft -lft -lreadline

SRC_DIR = srcs/

SRC_FILES = main.c			\
			get_cmd.c
SRC_FILES += parsing/parser.c	\
			 parsing/operators.c\
			 parsing/text.c		\
			 parsing/variables.c\
			 parsing/brackets.c	\
			 parsing/utils.c	\
			 parsing/wildcards.c	\
			 parsing/substitution.c	\
			 parsing/token.c	
SRC_FILES += builtins/cd.c		\
			 builtins/echo.c	\
			 builtins/env.c		\
			 builtins/exit.c	\
			 builtins/export.c	\
			 builtins/pwd.c		\
			 builtins/unset.c
SRC_FILES += data/env.c			\
			 data/init.c		\
			 data/prompt.c		\
			 data/utils.c		\
			 data/var_line.c	\
			 data/var.c
SRC_FILES += utils/error.c	\
			 utils/free.c	\
			 utils/str_builder.c
SRC_FILES += execution/assignments.c	\
			 execution/command.c		\
			 execution/execute.c		\
			 execution/file.c			\
			 execution/free.c			\
			 execution/heredoc.c		\
			 execution/path.c			\
			 execution/pipeline.c		\
			 execution/redirections.c	\
			 execution/routines.c
SRC_FILES += signals/signal_init.c	\
			 signals/input.c		\
			 signals/input_utils.c	\
			 signals/signal.c
			
SRC = $(addprefix $(SRC_DIR), $(SRC_FILES))

OBJ_DIR = objs/
OBJ_FILES = $(patsubst %.c, %.o, $(SRC_FILES))
OBJ = $(addprefix $(OBJ_DIR), $(OBJ_FILES))

INC_DIR = includes/
INCL = -I $(INC_DIR)

# COLORS
GREEN = \033[32m
BLUE    = \033[34m
VIOLET  = \033[38;5;93m
RESET = \033[0m

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJ)
	@make -s -C libft/
	@$(CC) $(FLAGS) $(SRC) $(INCL) -o $(NAME) $(LIBFT)
	@echo "⣿⣿⣿⣿⣿⡇⣬⡻⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿"
	@echo "⣿⣿⣿⣿⣿⡇⣿⣿⣮⡛⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿"
	@echo "⣿⣿⣿⣿⣿⡇⢹⣿⣿⣿⣦⡛⢈⠛⠙⠿⣛⣩⣥⢀⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿"
	@echo "⠟⢀⣝⡻⢿⣿⢸⣿⣿⣿⣿⣿⣶⣿⣿⣿⣿⣿⣇⣈⠉⣽⣿⣿⣿⠿⠿⣿⣿⣿"
	@echo "⡇⠼⣿⣿⣶⣌⠈⣡⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⣶⣶⣶⣶⣶⣶⣶⡶⢒⣴"
	@echo "⣿⣧⠹⣿⣿⣿⣾⣿⡿⢻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⢋⣴⣿⣿"
	@echo "⣿⣿⣧⠙⣹⣿⣿⡿⢱⡆⢿⣿⣿⣿⣿⣿⣿⣿⣿⢿⣿⣿⢿⠟⣫⣴⣿⣿⣿⣿"
	@echo "⣿⣿⣿⢰⣿⣿⠹⣧⠻⣇⡘⣿⣿⣿⣿⡿⠟⣩⡄⣿⣿⣿⠀⡚⠻⠿⠿⠿⣿⣿"
	@echo "⣿⣿⡇⣾⣿⣿⢰⡜⠳⣦⣥⣿⣿⣟⠩⢤⣿⠟⣰⣿⣿⣿⣸⣿⣿⣿⣿⡦⠜⣻"
	@echo "⣿⣿⡇⢿⣿⣿⣌⢡⣷⡄⣉⣛⠻⠿⠷⠶⠶⠞⢫⣿⣿⡿⣿⣿⠿⢛⣩⣥⣿⣿"
	@echo "⣿⣿⢃⠸⣿⣿⣿⣦⣙⠡⢿⣿⡿⢰⣿⡇⠜⣡⣿⣿⣿⢃⣥⣴⣾⣿⣿⣿⣿⣿"
	@echo "⣿⡏⢸⣦⣿⣿⣿⣿⣿⣿⣶⣦⣥⣭⣥⣶⣿⣿⣿⣿⢃⣾⣿⣿⣿⣿⣿⣿⣿⣿"
	@echo "⣿⣿⡘⢿⣿⡟⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣦⠡⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿"
	@echo "⣿⣿⣿⣦⠉⠉⠀⣝⠻⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡇⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿"
	@echo "⣿⣿⣿⣿⣿⣶⣿⣿⣿⣦⡀⠌⣡⣌⢻⣿⣿⣿⡿⢡⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿"
	@echo "⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣶⣿⣿⣆⠻⠿⢛⣴⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿"
	@echo ""
	@printf "$(GREEN)Minishell compiled successfully!$(RESET)\n"
	@printf "Made by $(VIOLET)Ego $(RESET)& $(BLUE)Petko $(RESET)\n"
	@echo ""

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)builtins
	@mkdir -p $(OBJ_DIR)data
	@mkdir -p $(OBJ_DIR)utils
	@mkdir -p $(OBJ_DIR)parsing
	@mkdir -p $(OBJ_DIR)execution
	@mkdir -p $(OBJ_DIR)signals

$(OBJ_DIR)%.o : $(SRC_DIR)%.c
	@$(CC) $(FLAGS) $(INCL) -c $< -o $@

clean:
	@make -s clean -C libft/
	@rm -rf $(OBJ_DIR)
	@printf "$(GREEN)Minishell clean up complete!$(RESET)\n"

fclean: clean
	@make -s fclean -C libft/
	@rm -f $(NAME)

re:
	@make -s fclean
	@make -s all

test: all
	@./minishell

norm:
	@norminette $(SRC) $(INC_DIR)

leaks:
	@valgrind --suppressions=.ignore_readline_leaks.supp --leak-check=full --show-leak-kinds=all --track-origins=yes ./minishell
