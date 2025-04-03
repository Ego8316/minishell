# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ego <ego@student.42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/27 21:17:01 by pkurt             #+#    #+#              #
#    Updated: 2025/04/03 21:15:29 by ego              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = gcc
FLAGS = -Wall -Wextra -Werror
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
			 parsing/token.c	
SRC_FILES += builtins/cd.c		\
			 builtins/echo.c	\
			 builtins/env.c		\
			 builtins/exit.c	\
			 builtins/export.c	\
			 builtins/pwd.c		\
			 builtins/unset.c
SRC_FILES += data/init.c	\
			 data/utils.c	\
			 data/env.c		\
			 data/var.c		\
			 data/var_line.c
SRC_FILES += utils/error.c	\
			 utils/free.c
SRC_FILES += execution/command.c	\
			 execution/pipeline.c	\
			 execution/path.c
SRC_FILES += signals/signal_init.c
			
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
