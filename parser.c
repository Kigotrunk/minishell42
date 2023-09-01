/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kallegre <kallegre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 15:01:12 by kallegre          #+#    #+#             */
/*   Updated: 2023/08/31 12:17:35 by kallegre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pipe_count(char **argv)
{
	int	n;
	int	i;

	n = 0;
	i = 0;
	while (argv[i])
	{
		if (argv[i][0] == '|')
			n++;
		i++;
	}
	return (n);
}

int	pipe_len(char **tab)
{
	int	i;

	i = 0;
	while (tab[i] && tab[i][0] != '|')
		i++;
	return (i);
}

char	**get_pipe(char **tab)
{
	char	**argv;
	int		ac;
	int		i;

	ac = pipe_len(tab);
	argv = (char **)malloc((ac + 1) * sizeof(char *));
	i = 0;
	while (i < ac)
	{
		argv[i] = ft_strdup(tab[i]);
		i++;
	}
	argv[i] = NULL;
	return (argv);
}

char	***get_pipe_tab(char **tab)
{
	char	***cmd_tab;
	int		i;
	int		k;

	cmd_tab = cmd_tab_init(pipe_count(tab) + 2);
	i = 0;
	k = 0;
	while (tab[i])
	{
		if (tab[i][0] == '|')
		{
			i++;
			k++;
		}
		else
		{
			cmd_tab[k] = get_pipe(tab + i);
			while (tab[i] && tab[i][0] != '|')
				i++;
		}
	}
	cmd_tab[k + 1] = NULL;
	return (cmd_tab);
}

char	***cmd_tab_init(int n)
{
	char	***cmd_tab;
	int		i;

	cmd_tab = (char ***)malloc(n * sizeof(char **));
	i = 0;
	while (i < n)
	{
		cmd_tab[i] = NULL;
		i++;
	}
	return (cmd_tab);
}
