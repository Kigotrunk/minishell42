/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kallegre <kallegre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 11:58:03 by kallegre          #+#    #+#             */
/*   Updated: 2023/09/07 11:54:09 by kallegre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	only_builtin(t_vars va, t_env **env)
{
	char	**argv;
	int		*heredoc;
	int		code;
	int		fd[3];

	fd_save(fd);
	heredoc = NULL;
	va.fd_0 = fd[0];
	code = get_io(va.argv[0], &heredoc, env, va);
	if (code)
		return (code);
	if (heredoc != NULL)
	{
		dup2(heredoc[0], 0);
		close(heredoc[0]);
	}
	argv = get_argv(va.argv[0], env, va.err_code);
	argv = remove_wrg_arg(argv);
	code = do_builtin(argv, env);
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
	va.n = cmd_count(argv);
	if (va.n == 0)
		return (0);
	if (va.n == 1 && is_builtin(find_cmd_name(argv[0])))
		return (only_builtin(va, env));
	if (va.n == 1 && is_new_var_cmd(argv[0]))
		return (get_new_var(argv[0], *env));
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

	make_redir(env, va, k);
	argv = get_argv(va.argv[k], env, va.err_code);
	argv = remove_wrg_arg(argv);
	if (argv == NULL)
		exit(0);
	if (!is_builtin(argv[0]))
		path = pathfinder(argv[0], va.envp);
	if (ft_strncmp(argv[0], "grep", 5) == 0 
		|| ft_strncmp(argv[0], "cat", 4) == 0)
		signal(SIGQUIT, SIG_DFL);
	if (is_builtin(argv[0]))
	{
		code = do_builtin(argv, env);
		free_tab(argv);
		exit(code);
	}
	else
		execve(path, argv, va.envp);
}

void	make_redir(t_env **env, t_vars va, int k)
{
	int		*heredoc;
	int		code;

	va.fd_0 = dup(0);
	if (k != 0)
		dup2(va.fd[k - 1][0], 0);
	if (k != va.n - 1)
		dup2(va.fd[k][1], 1);
	heredoc = NULL;
	code = get_io(va.argv[k], &heredoc, env, va);
	if (code)
		exit(code);
	if (heredoc != NULL)
	{
		dup2(heredoc[0], 0);
		close(heredoc[0]);
	}
	close(va.fd_0);
	close_all(va.n, va.fd);
}
