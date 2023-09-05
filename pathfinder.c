/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinder.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kallegre <kallegre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 10:44:10 by kallegre          #+#    #+#             */
/*   Updated: 2023/09/04 12:11:48 by kallegre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*pathfinder(char *str, char **envp)
{
	char	**split;
	char	*temp;
	int		i;

	if (access(str, F_OK | X_OK) == 0 && open(str, O_DIRECTORY) == -1)
		return (str);
	i = check_path(str, envp);
	split = ft_split(envp[i] + 5, ':');
	i = 0;
	while (split[i])
	{
		temp = ft_strjoin_path(split[i], str);
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

	dup2(2, 1);
	i = 0;
	while (str[i])
	{
		if (str[i] == '/')
		{
			if (access(str, F_OK | X_OK) == 0)
			{
				print_err("minishell: ?: Is a directory", str);
				exit(126);
			}
			if (access(str, F_OK) == 0)
			{
				print_err("minishell: ?: Permission denied", str);
				exit(126);
			}
			print_err("minishell: ?: No such file or directory", str);
			exit(127);
		}
		i++;
	}
	print_err("?: command not found", str);
}

int	check_path(char *str, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (i);
		i++;
	}
	print_err("minishell: ?: No such file or directory", str);
	exit(127);
}

char	*ft_strjoin_path(char const *s1, char const *s2)
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
	while (*s2)
	{
		s[i] = *s2;
		s2++;
		i++;
	}
	s[i] = '\0';
	return (s);
}
