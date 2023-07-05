/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kortolan <kortolan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 11:58:03 by kallegre          #+#    #+#             */
/*   Updated: 2023/07/05 14:37:39 by kortolan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pipex(char ***argv, char **io_list, t_env **env)
{
	t_vars	va;
	int		i;

	if (io_list[0][0])
	{
		if (access(io_list[0], F_OK) == -1)
		{
			perror(io_list[0]);
			return (1);
		}
	}
	va.argv = argv;
	va.io_lst = io_list;
	va.n = tab_size(argv);
	if (va.n == 0)
		return(0);
	va.fd = (int **)malloc(sizeof(int *) * (va.n - 1));
	i = 0;
	while (i < va.n - 1)
	{
		va.fd[i] = (int *)malloc(sizeof(int) * 2);
		if (pipe(va.fd[i]) == -1)
			return (1);
		i++;
	}
	va.pid = (int *)malloc(sizeof(int) * va.n);
	return (exec_cmd(env, va));
}

int	exec_cmd(t_env **env, t_vars va)
{
	int		i;

	i = 0;
	while (i < va.n)
	{
		va.envp = get_tab_env(*env);
		va.pid[i] = fork();
		if (va.pid[i] < 0)
			return (1);
		if (va.pid[i] == 0)
			cmd(env, va, i);
		i++;
		free_tab(va.envp);
	}
	close_all(va.n, va.fd);
	free_fd(va.fd, va.n);
	return (check_errors(va.pid, va.n));
}

void	cmd(t_env **env, t_vars va, int k)
{
	char	*path;

	redir_err(va);
	if (!is_builtin(va.argv[k][0]))
		path = pathfinder(va.argv[k][0], va.envp);
	redir_input(va, k);
	redir_output(va, k);
	close_all(va.n, va.fd);
	if (is_builtin(va.argv[k][0]))
		do_builtin(va.argv[k], env, va.envp);
	else
	{
		execve(path, va.argv[k], va.envp);
		free(path);
	}
}