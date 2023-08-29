/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kallegre <kallegre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 17:26:25 by kallegre          #+#    #+#             */
/*   Updated: 2023/08/29 10:44:05 by kallegre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**remove_wrg_arg(char **argv)
{
	char	**new_argv;
	int		i;
	int		j;

	j = 0;
	i = 0;
	while (argv[i])
	{
		if (argv[i] != NULL && argv[i][0] != '\0' && argv[i][0] != ' ')
			j++;
		i++;
	}
	new_argv = (char **)malloc(sizeof(char *) * (j + 1));
	i = 0;
	j = -1;
	while (argv[i])
	{
		if (argv[i] != NULL && argv[i][0] != '\0' && argv[i][0] != ' ')
			new_argv[++j] = ft_strdup(argv[i]);
		i++;
	}
	new_argv[++j] = NULL;
	return (new_argv);
}

int	check_errors(int *pid, int n)
{
	int	status;
	int	i;

	i = 0;
	while (i < n)
	{
		waitpid(pid[i], &status, 0);
		if (WEXITSTATUS(status) != 0)
		{
			free(pid);
			return (WEXITSTATUS(status));
		}
		i++;
	}
	free(pid);
	return (0);
}

void	close_all(int n, int **fd)
{
	int	i;

	i = 0;
	while (i + 1 < n)
	{
		close(fd[i][0]);
		close(fd[i][1]);
		i++;
	}
}

void	free_fd(t_vars va)
{
	int	i;

	i = 0;
	while (i + 1 < va.n)
	{
		free(va.fd[i]);
		i++;
	}
	free(va.fd);
	free(va.heredoc);
}
