/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kallegre <kallegre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 11:58:03 by kallegre          #+#    #+#             */
/*   Updated: 2023/08/31 12:05:41 by kallegre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	only_builtin(t_vars va, t_env **env)
{
	char	**argv;
	int		*heredoc;
	int		code;
	int		fd[3];

	fd[0] = dup(0);
	fd[1] = dup(1);
	fd[2] = dup(2);
	heredoc = NULL;
	code = get_io(va.argv[0], &heredoc, **env, va.err_code);
	if (code)
		exit(code);
	if (heredoc != NULL)
	{
		dup2(heredoc[0], 0);
		close(heredoc[0]);
	}
	va.envp = get_tab_env(*env);
	argv = get_argv(va.argv[0], **env, va.err_code);
	argv = remove_wrg_arg(argv);
	code = do_builtin(argv, env, va.envp);
	free_tab(va.envp);
	free_tab(argv);
	fd_back(fd);
	return (code);
}

int	pipex(t_env **env, char ***argv, int err_code)
{
	t_vars	va;
	int		i;

	va.err_code = err_code;
	va.argv = argv;
	va.n = tab_size(argv);
	if (va.n == 0)
		return (0);
	if (va.n == 1 && is_builtin(find_cmd_name(argv[0])))
		return (only_builtin(va, env));
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
	free_fd(va);
	return (check_errors(va.pid, va.n));
}

void	cmd(t_env **env, t_vars va, int k)
{
	int		code;
	char	**argv;
	char	*path;

	make_redir(**env, va, k);
	argv = get_argv(va.argv[k], **env, va.err_code);
	argv = remove_wrg_arg(argv);
	if (argv == NULL)
		exit(0);
	if (!is_builtin(argv[0]))
		path = pathfinder(argv[0], va.envp);
	if (is_builtin(argv[0]))
	{
		code = do_builtin(argv, env, va.envp);
		free_tab(argv);
		exit(code);
	}
	else
		execve(path, argv, va.envp);
}

void	make_redir(t_env env, t_vars va, int k)
{
	int		*heredoc;
	int		code;

	if (k != 0)
		dup2(va.fd[k - 1][0], 0);
	if (k != va.n - 1)
		dup2(va.fd[k][1], 1);
	heredoc = NULL;
	code = get_io(va.argv[k], &heredoc, env, va.err_code);
	if (code)
		exit(code);
	if (heredoc != NULL)
	{
		dup2(heredoc[0], 0);
		close(heredoc[0]);
	}
	close_all(va.n, va.fd);
}
