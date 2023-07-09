# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kortolan <kortolan@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/19 12:03:07 by kortolan          #+#    #+#              #
#    Updated: 2023/07/09 14:07:58 by kortolan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC         =     gcc

CFLAGS     =     -Wall -Wextra -Werror

LIBFT    =    ft_printf/libftprintf.a

SRCS     =  main.c \
			get_next_line/get_next_line_bonus.c \
			get_next_line/get_next_line_utils_bonus.c \
			builtin_1.c \
			builtin_2.c \
			new_env.c \
			minishell_utils.c \
			builtin_echo.c \
			parsing1.c \
			builtin_parsing_utils.c \
			parser.c \
			lexer.c \
			lexer_utils.c \
			utils.c \
			pipex.c \
			redirection.c \
			pipex_utils.c \
			builtin_unset.c \
			builtin_exit.c \
			builtin_cd.c \
			builtin_export.c \
			builtin_env.c \
			signal.c \
											

OBJS    = $(SRCS:.c=.o)
            
NAME = minishell

all:    $(NAME)

$(NAME):    $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -lreadline -L/Users/$(USER)/.brew/opt/readline/lib -I/Users/$(USER)/.brew/opt/readline/include -o $(NAME) $(LIBFT)

$(LIBFT):
	make -C ft_printf

clean:
	make clean -C ft_printf
	rm -rf $(OBJS)

fclean: clean
	rm -rf ft_printf/libftprintf.a
	rm -rf $(NAME)

re: fclean all
