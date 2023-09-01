/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_io.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kallegre <kallegre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 12:16:17 by kallegre          #+#    #+#             */
/*   Updated: 2023/08/31 12:17:42 by kallegre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	**get_argv(char **tab, t_env env, int err_code)
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
			argv[j] = replace_quote(tab[i], env, err_code);
			j++;
			i++;
		}
	}
	argv[j] = NULL;
	return (argv);
}

int	get_io(char **argv, int **heredoc, t_env env, int err_code)
{
	char	*filename;
	int		code;
	int		i;

	code = 0;
	i = 0;
	while (argv[i])
	{
		if (is_ope(argv[i]) && argv[i][0] != '|')
		{
			filename = replace_quote(argv[i + 1], env, err_code);
			code = replace_io(argv[i], filename, heredoc);
			free(filename);
			if (code)
				return (code);
			i++;
		}
		i++;
	}
	return (0);
}

int	replace_io(char *ope, char *filename, int **heredoc)
{
	int	code;

	code = 0;
	if (ope[0] == '<')
	{
		code = redir_in(ope, filename, heredoc);
		if (code)
			return (code);
	}
	if (ope[0] == '>')
	{
		code = redir_out(ope, filename);
		if (code)
			return (code);
	}
	if (ope[0] == '2' && ope[1] == '>')
	{
		code = redir_err(ope, filename);
		if (code)
			return (code);
	}
	return (0);
}
