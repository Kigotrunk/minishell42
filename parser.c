/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kallegre <kallegre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 15:01:12 by kallegre          #+#    #+#             */
/*   Updated: 2023/08/24 12:09:02 by kallegre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	syntax_error(char **argv)
{
	int	i;

	i = 0;
	if (argv[0][0] == '|')
		return (1);
	while (argv[i + 1])
	{
		if (is_ope(argv[i]) && is_ope(argv[i + 1]))
			return (1);
		i++;
	}
	if (is_ope(argv[i]))
		return (1);
	return (0);
}

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

int	redir_count(char **argv)
{
	int	n;
	int	i;

	n = 0;
	i = 0;
	while (argv[i])
	{
		if (argv[i][0] == '<' || argv[i][0] == '>')
			n++;
		i++;
	}
	return (n);
}

int	args_count(char **tab)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (tab[i] && tab[i][0] != '|')
	{
		if (is_ope(tab[i]))
			i += 2;
		else
		{
			count++;
			i++;
		}
	}
	return (count);
}

char	**get_argv(char **tab)
{
	char	**argv;
	int		ac;
	int		i;
	int		j;

	ac = args_count(tab);
	argv = (char **)malloc((ac + 1) * sizeof(char *));
	i = 0;
	j = 0;
	while (j < ac)
	{
		if (is_ope(tab[i]))
			i += 2;
		else
		{
			argv[j] = ft_strdup(tab[i]);
			j++;
			i++;
		}
	}
	argv[j] = NULL;
	return (argv);
}

char	***get_cmd_tab(char **tab)
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
		else if (is_ope(tab[i]))
			i += 2;
		else
		{
			cmd_tab[k] = get_argv(tab + i);
			while (tab[i] && tab[i][0] != '|')
				i++;
		}
	}
	cmd_tab[k + 1] = NULL;
	return (cmd_tab);
}

char	**get_io(char **argv)
{
	char	**io_tab;
	int		i;

	io_tab = io_init();
	i = 0;
	while (argv[i])
	{
		if (is_ope(argv[i]) && argv[i][0] != '|')
		{
			replace_io(io_tab, argv[i], argv[i + 1]);
			i++;
		}
		i++;
	}
	return (io_tab);
}

void	replace_io(char **io_tab, char *ope, char *filename)
{
	int	tmp_fd;
	int	k;

	if (ope[0] == '<')
		k = 0;
	if (ope[0] == '>')
		k = 1;
	if (ope[0] == '2' && ope[1] == '>')
		k = 2;
	free(io_tab[k]);
	io_tab[k] = ft_strjoin(ope, filename);
	if (k > 0)
	{
		tmp_fd = open(filename, O_CREAT, 0644);
		close (tmp_fd);
	}
}

char	**io_init(void)
{
	char	**io_tab;
	int		i;

	io_tab = (char **)malloc(4 * sizeof(char *));
	i = 0;
	while (i < 3)
	{
		io_tab[i] = malloc(1);
		io_tab[i][0] = '\0';
		i++;
	}
	io_tab[i] = NULL;
	return (io_tab);
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

char	*ft_stradd(char *s1, char *s2)
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
	free(s1 - i);
	s[i] = ' ';
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
