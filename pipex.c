/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kortolan <kortolan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 11:58:03 by kallegre          #+#    #+#             */
/*   Updated: 2023/07/13 13:32:07 by kortolan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pipex(t_env **env, char ***argv, char **io_list)
{
	t_vars	va;
	char	**ptr;
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
	if (va.n == 1)
	{
		ptr = remove_wrg_arg(argv[0]);
		ptr = get_new_var(ptr, *env);
		if (ptr == NULL || ptr[0] == NULL)
			return (0);
		va.argv = &ptr;
		if (is_builtin(ptr[0]))
		{
			va.envp = get_tab_env(*env);
			do_builtin(ptr, env, va.envp);
			//free_tab(ptr);
			free_tab(va.envp);
			return (0);
		}
	}
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