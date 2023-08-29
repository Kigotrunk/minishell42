/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kallegre <kallegre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 15:04:14 by kallegre          #+#    #+#             */
/*   Updated: 2023/08/29 09:31:36 by kallegre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	signal(SIGQUIT, ft_sig);
	while (1)
	{
		input = readline("\e[0;34mminishell$ \e[0m");
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
	char	***cmd_tab;
	int		fd_save[3];
	int		*heredoc;
	int		new_code;

	if (argv == NULL)
		return (0);
	if (syntax_error(argv))
		return (258);
	fd_save[0] = dup(0);
	fd_save[1] = dup(1);
	fd_save[2] = dup(2);
	heredoc = NULL;
	new_code = 0;
	new_code = get_io(argv, &heredoc, **env, err_code);
	cmd_tab = get_cmd_tab(argv, **env, err_code);
	if (new_code == 0)
		new_code = pipex(env, cmd_tab, heredoc);
	fd_back(fd_save);
	free_tab_tab(cmd_tab);
	return (new_code);
}
