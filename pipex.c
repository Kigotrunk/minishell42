/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kallegre <kallegre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 11:58:03 by kallegre          #+#    #+#             */
/*   Updated: 2023/08/23 12:51:19 by kallegre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	only_builtin(t_vars *va, t_env **env)
{
	int	fd[3];

	fd[0] = dup(0);
	fd[1] = dup(1);
	fd[2] = dup(2);
	redir_err(*va);
	redir_input(*va, 0);
	redir_output(*va, 0);
	va->envp = get_tab_env(*env);
	do_builtin(va->argv[0], env, va->envp);
	free_tab(va->envp);
	dup2(fd[0], 0);
	dup2(fd[1], 1);
	dup2(fd[2], 2);
	close(fd[0]);
	close(fd[1]);
	close(fd[2]);
	return (0);
}

int	pipex(t_env **env, char ***argv, char **io_list)
{
	t_vars	va;
	int		i;

	va.argv = argv;
	va.io_lst = io_list;
	va.n = tab_size(argv);
	if (va.io_lst[0][0] && va.io_lst[0][1] == '<')
		heredoc(&va, end_ope(va.io_lst[0]));
	if (va.n == 0)
		return(0);
	if (va.n == 1 && is_builtin(argv[0][0]))
		return (only_builtin(&va, env));
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
	int		code;
	char	**argv;
	char	*path;

	argv = remove_wrg_arg(va.argv[k]);
	redir_err(va);
	if (!is_builtin(va.argv[k][0]))
		path = pathfinder(va.argv[k][0], va.envp);
	redir_input(va, k);
	redir_output(va, k);
	close_all(va.n, va.fd);
	if (is_builtin(va.argv[k][0]))
	{
		code = do_builtin(argv, env, va.envp);
		free_tab(argv);
		exit(code);
	}
	else
		execve(path, argv, va.envp);
}