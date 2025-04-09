# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ego <ego@student.42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/25 18:54:06 by ego               #+#    #+#              #
#    Updated: 2025/04/09 23:03:47 by ego              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SDIR		=	./
SRCS		=	ft_atoi.c			\
				ft_bzero.c			\
				ft_calloc.c			\
				ft_char_in_str.c	\
				ft_isalnum.c		\
				ft_isalpha.c		\
				ft_isascii.c		\
				ft_isdigit.c		\
				ft_isprint.c		\
				ft_isspace.c		\
				ft_itoa.c			\
				ft_lstadd_back.c	\
				ft_lstadd_front.c	\
				ft_lstclear.c		\
				ft_lstdelone.c		\
				ft_lstiter.c		\
				ft_lstlast.c		\
				ft_lstmap.c			\
				ft_lstnew.c			\
				ft_lstsize.c		\
				ft_memchr.c			\
				ft_memcmp.c			\
				ft_memcpy.c			\
				ft_memmove.c		\
				ft_memset.c			\
				ft_putchar_fd.c		\
				ft_putendl_fd.c		\
				ft_putnbr_fd.c		\
				ft_putstr_fd.c		\
				ft_split.c			\
				ft_strchr.c			\
				ft_strcmp.c			\
				ft_strdup.c			\
				ft_stristype.c		\
				ft_striteri.c		\
				ft_strjoin.c		\
				ft_strlcat.c		\
				ft_strlcpy.c		\
				ft_strlen.c			\
				ft_strmapi.c		\
				ft_strncmp.c		\
				ft_strndup.c		\
				ft_strnstr.c		\
				ft_strrchr.c		\
				ft_strtrim.c		\
				ft_substr.c			\
				ft_tolower.c		\
				ft_toupper.c		\
				get_next_line.c		\
				join_strs.c
ODIR		=	objs/
OBJS		=	$(addprefix $(ODIR), $(SRCS:.c=.o))
IDIR		=	.

CC			=	cc
RM			=	rm -rf
AR			=	ar rcs
CFLAGS		=	-Wall -Wextra -Werror

NAME		=	libft.a

all			:	$(NAME)

$(NAME)		:	$(ODIR) $(OBJS) header
				echo "Creating archive..." && \
				$(AR) $(NAME) $(OBJS) && \
				echo "Generating index..." && \
				ranlib $(NAME) && \
				printf "$(COLOR_G)[OK] libft is ready!$(C_RESET)\n" || \
				printf "$(COLOR_R)[KO] Something went wrong.$(C_RESET)\n"

$(ODIR)		:
				mkdir -p $(ODIR) && echo "Creating object directory..."

$(ODIR)%.o	:	$(SDIR)%.c
				echo "Compiling $<..."
				$(CC) $(CFLAGS) -I $(IDIR) -c $< -o $@ || \
				(printf "$(COLOR_R)[KO] Compilation failed.$(C_RESET)\n" && false)

norm		:
				norminette -R CheckForbiddenSourceHeader $(SRCS) libft.h

clean		:
				echo "Removing object files..."
				$(RM) $(ODIR)
				printf "$(COLOR_O)[OK] All object files have been removed.$(C_RESET)\n"

fclean		:	clean
				echo "Removing binary files..."
				$(RM) $(NAME)
				printf "$(COLOR_O)[OK] All binary files have been removed.$(C_RESET)\n"

re			:	fclean all

.PHONY		:	all clean fclean re
.SILENT		:	all $(NAME) $(ODIR) $(OBJS) norm clean fclean re header

COLOR_R		= \033[31m
COLOR_O		= \033[38;5;214m
COLOR_Y		= \033[33m
COLOR_G		= \033[32m
COLOR_B		= \033[34m
COLOR_V		= \033[38;5;93m
COLOR_I		= \033[3m
C_RESET		= \033[0m

header	:
			printf "============================\n"
			printf "$(COLOR_R)  _      _  _       __  _   	$(C_RESET)\n"
			printf "$(COLOR_O) | |    (_)| |__   / _|| |_ 	$(C_RESET)\n"
			printf "$(COLOR_Y) | |    | || '_ \ | |_ | __|	$(C_RESET)\n"
			printf "$(COLOR_G) | |___ | || |_) ||  _|| |_ 	$(C_RESET)\n"
			printf "$(COLOR_B) |_____||_||_.__/ |_|   \__|	$(C_RESET)\n"
			printf "$(COLOR_I)$(COLOR_V)           by Ego	$(C_RESET)\n"
			printf "============================\n"
