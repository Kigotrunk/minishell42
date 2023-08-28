/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kallegre <kallegre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 15:04:14 by kallegre          #+#    #+#             */
/*   Updated: 2023/08/28 12:25:03 by kallegre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int err_code;

int main(int argc, char **argv, char **envp)
{
	t_env   *env;
	char    *input;
	char    **args;

	(void)argc;
	(void)argv;
	env = cpy_env(envp);
	err_code = 0;
	signal(SIGINT, ft_sig);
	signal(SIGQUIT, ft_sig);
	while ((input = readline("\e[0;34mminishell$ \e[0m")))
	{
		if (input == NULL)
			exit(1);
		add_history(input);
		if (quote_check(input) != 0)
		{
			free(input);
			input = NULL;
			ft_printf("Error\n");
			continue ;
		}
		args = split_args(input);
		err_code = minishell(&env, args);
		free(input);
		input = NULL;
		free_tab(args);
		args = NULL;
	}
	ft_lstclear(&env, &free);
	return (0);
}

int    minishell(t_env **env, char **argv)
{
	char    ***cmd_tab;
	int     fd_save[3];
	int     *heredoc;
	int		new_code;

	if (argv == NULL)
		return (0);
	if (syntax_error(argv))
	{
		ft_printf("Syntax error\n");
		return (258);
	}

	argv = ft_fix_args(argv, env); //leak
	cmd_tab = get_cmd_tab(argv);
	
	fd_save[0] = dup(0);
	fd_save[1] = dup(1);
	fd_save[2] = dup(2);
	heredoc = NULL;
	new_code = get_io(argv, &heredoc);
	
	//argv = ft_fix_args(argv, env); //leak
	//cmd_tab = get_cmd_tab(argv);
	
	if (new_code == 0)
		new_code = pipex(env, cmd_tab, heredoc);

	dup2(fd_save[0], 0);
	dup2(fd_save[1], 1);
	dup2(fd_save[2], 2);
	close(fd_save[0]);
	close(fd_save[1]);
	close(fd_save[2]);
	free_tab_tab(cmd_tab);
	return (new_code);
}