/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kallegre <kallegre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 15:04:14 by kallegre          #+#    #+#             */
/*   Updated: 2023/08/30 14:30:41 by kallegre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	sig;

int	main(int argc, char **argv, char **envp)
{
	t_env	*env;
	char	*input;
	char	**args;
	int		err_code;

	(void)argc;
	(void)argv;
	env = cpy_env(envp);
	err_code = 0;
	signal(SIGINT, ft_sig);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		sig = 0;
		input = readline("\e[0;34mminishell$ \e[0m");
		sig = 1;
		if (input == NULL)
			break ;
		add_history(input);
		if (quote_check(input) != 0)
			continue ;
		args = split_args(input);
		err_code = minishell(&env, args, err_code);
		free(input);
		free_tab(args);
	}
	return (ft_lstclear(&env, &free));
}

int	minishell(t_env **env, char **argv, int err_code)
{
	char	***pipe_tab;
	int		fd_save[3];

	if (argv == NULL)
		return (0);
	if (syntax_error(argv))
		return (258);
	fd_save[0] = dup(0);
	fd_save[1] = dup(1);
	fd_save[2] = dup(2);
	pipe_tab = get_pipe_tab(argv);
	err_code = pipex(env, pipe_tab, err_code);
	fd_back(fd_save);
	free_tab_tab(pipe_tab);
	return (err_code);
}

void    ft_sig(int code)
{
    if (code == SIGINT)
    {
		ft_printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		if (sig == 0)
			rl_redisplay();
    }
	if (code == SIGQUIT)
		ft_printf("Quit\n");
}
