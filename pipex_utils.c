/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kallegre <kallegre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 17:26:25 by kallegre          #+#    #+#             */
/*   Updated: 2023/07/03 17:13:17 by kallegre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	err_code;

char	*pathfinder(char *str, char **envp)
{
	char	**split;
	char	*temp;
	int		i;

	if (access(str, F_OK | X_OK) == 0)
		return (str);
	i = 0;
	while (!ft_strnstr(envp[i], "PATH=", 5))
		i++;
	split = ft_split(envp[i] + 5, ':');
	i = 0;
	while (split[i])
	{
		temp = ft_strjoin2(split[i], str);
		if (access(temp, F_OK | X_OK) == 0)
		{
			free_tab(split);
			return (temp);
		}
		free(temp);
		i++;
	}
	free_tab(split);
	path_error(str);
	exit(127);
}

void	path_error(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '/')
		{
			ft_printf("minishell: %s: No such file or directory\n", str);
			err_code = 127;
			return ;
		}
		i++;
	}
	ft_printf("minishell: %s: command not found\n", str);
	err_code = 127;
}

char	*ft_strjoin2(char const *s1, char const *s2)
{
	char	*s;
	int		i;

	s = malloc(ft_strlen(s1) + ft_strlen(s2) + 2);
	if (s == NULL)
		return (NULL);
	i = 0;
	while (*s1)
	{
		s[i] = *s1;
		s1++;
		i++;
	}
	s[i] = '/';
	i++;
	while (*s2 && *s2 != ' ')
	{
		s[i] = *s2;
		s2++;
		i++;
	}
	s[i] = '\0';
	return (s);
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

void	free_fd(int **fd, int n)
{
	int	i;

	i = 0;
	while (i + 1 < n)
	{
		free(fd[i]);
		i++;
	}
	free(fd);
}