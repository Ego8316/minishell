# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ego <ego@student.42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/25 18:54:06 by ego               #+#    #+#              #
#    Updated: 2025/03/14 14:10:10 by ego              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	=	ft_isalpha.c		\
			ft_isdigit.c		\
			ft_isalnum.c		\
			ft_isascii.c		\
			ft_isprint.c		\
			ft_isspace.c		\
			ft_strlen.c			\
			ft_memset.c			\
			ft_bzero.c			\
			ft_memcpy.c			\
			ft_memmove.c		\
			ft_strlcpy.c		\
			ft_strlcat.c		\
			ft_toupper.c		\
			ft_tolower.c		\
			ft_strchr.c			\
			ft_strrchr.c		\
			ft_memchr.c			\
			ft_memcmp.c			\
			ft_strcmp.c			\
			ft_strncmp.c		\
			ft_strnstr.c		\
			ft_atoi.c			\
			ft_calloc.c			\
			ft_strdup.c			\
			ft_strndup.c		\
			ft_substr.c			\
			ft_strjoin.c		\
			ft_strtrim.c		\
			ft_split.c			\
			ft_itoa.c			\
			ft_strmapi.c		\
			ft_striteri.c		\
			ft_putchar_fd.c		\
			ft_putstr_fd.c		\
			ft_putendl_fd.c		\
			ft_putnbr_fd.c		\
			join_strs.c			\
			get_next_line.c
BSRCS	=	ft_lstnew.c			\
			ft_lstadd_front.c	\
			ft_lstsize.c		\
			ft_lstlast.c		\
			ft_lstadd_back.c	\
			ft_lstdelone.c		\
			ft_lstclear.c		\
			ft_lstiter.c		\
			ft_lstmap.c
OBJS	=	$(SRCS:.c=.o)
BOBJS	=	$(BSRCS:.c=.o)
IDIR	=	.

CC		=	cc
RM		=	rm -f
AR		=	ar rcs
CFLAGS	=	-Wall -Wextra -Werror

NAME	=	libft.a

all		:	bonus

$(NAME)	:	$(OBJS) header
			echo "Creating archive..."
			$(AR) $(NAME) $(OBJS)
			echo "Generating index..."
			ranlib $(NAME)
			printf "$(GREEN)[OK] libft is ready!$(RESET)\n"

bonus	:	$(OBJS) $(BOBJS) header
			echo "Creating archive with bonus..."
			$(AR) $(NAME) $(OBJS) $(BOBJS)
			echo "Generating index..."
			ranlib $(NAME)
			printf "$(GREEN)[OK] libft with bonus is ready!$(RESET)\n"
.c.o	:
			echo "Compiling $<..."
			$(CC) $(CFLAGS) -I $(IDIR) -c $< -o $(<:.c=.o)

norm	:
			norminette -R CheckForbiddenSourceHeader $(SRCS) $(BSRCS) libft.h

clean	:
			echo "Removing object files..."
			$(RM) $(OBJS) $(BOBJS)
			printf "$(ORANGE)[OK] All object files have been removed.$(RESET)\n"

fclean	:	clean
			echo "Removing binary files..."
			$(RM) $(NAME)
			printf "$(ORANGE)[OK] All binary files have been removed.$(RESET)\n"

re		:	fclean all

.PHONY	:	all clean fclean re
.SILENT	:	all $(NAME) $(OBJS) $(BOBJS) norm clean fclean re header test bonus

RED     = \033[31m
ORANGE  = \033[38;5;214m
YELLOW  = \033[33m
GREEN   = \033[32m
BLUE    = \033[34m
VIOLET  = \033[38;5;93m
ITALIC  = \033[3m
RESET   = \033[0m

header	:
			printf "============================\n"
			printf "$(RED)  _      _  _       __  _   $(RESET)\n"
			printf "$(ORANGE) | |    (_)| |__   / _|| |_ $(RESET)\n"
			printf "$(YELLOW) | |    | || '_ \ | |_ | __|$(RESET)\n"
			printf "$(GREEN) | |___ | || |_) ||  _|| |_ $(RESET)\n"
			printf "$(BLUE) |_____||_||_.__/ |_|   \__|$(RESET)\n"
			printf "$(ITALIC)$(VIOLET)           by Ego           $(RESET)\n"
			printf "============================\n"
