# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kallegre <kallegre@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/19 12:03:07 by kortolan          #+#    #+#              #
#    Updated: 2023/08/29 11:16:00 by kallegre         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC         =     gcc

CFLAGS     =     -Wall -Wextra -Werror

LIBFT    =    ft_printf/libftprintf.a

SRCS     =  main.c \
			get_next_line/get_next_line_bonus.c \
			get_next_line/get_next_line_utils_bonus.c \
			builtin.c \
			new_env.c \
			lst_utils.c \
			builtin_echo.c \
			parser.c \
			lexer.c \
			lexer_utils.c \
			utils.c \
			utils_2.c \
			pipex.c \
			pathfinder.c \
			redirection.c \
			pipex_utils.c \
			builtin_unset.c \
			builtin_exit.c \
			builtin_cd.c \
			builtin_export.c \
			builtin_env.c \
			signal.c \
			new_var.c \
			replace_quote.c \
											

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

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@printf "\033[1mcompiling\033[0m: $<                     \r"
#	@say "compiling file $<, please stand by"

re: fclean all

.PHONY:	clean fclean re all
