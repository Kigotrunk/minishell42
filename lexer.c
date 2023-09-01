/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kallegre <kallegre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 13:55:47 by kallegre          #+#    #+#             */
/*   Updated: 2023/08/31 12:28:38 by kallegre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	arg_c(char *str)
{
	int	n;

	n = 0;
	while (*str)
	{
		while (*str == ' ')
			str++;
		if (*str == '\n' || *str == '\0')
			return (n);
		else
		{
			n++;
			if (is_ope(str))
				str = end_ope(str);
			else if (*str == '\"' || *str == '\'')
				str = eoa_quote(str, *str);
			else
				str = eoa_str(str);
		}
	}
	return (n);
}

int	arg_len(char *str)
{
	int	i;

	i = 0;
	if (*str == '\'' || *str == '\"')
		i = eoa_quote(str, *str) - str;
	else if (is_ope(str))
		i = end_ope(str) - str;
	else
		i = eoa_str(str) - str;
	return (i);
}

char	*cpy_arg(char *str)
{
	int		i;
	int		len;
	char	*arg;

	i = 0;
	len = arg_len(str);
	arg = (char *)malloc((len + 1) * sizeof(char));
	if (arg == NULL)
		return (NULL);
	while (i < len)
	{
		arg[i] = str[i];
		i++;
	}
	arg[i] = '\0';
	return (arg);
}

char	**split_args(char *str)
{
	char	**tab;
	int		ac;
	int		i;

	ac = arg_c(str);
	if (ac == 0)
		return (NULL);
	tab = (char **)malloc((ac + 1) * sizeof(char *));
	if (tab == NULL)
		return (NULL);
	i = 0;
	while (*str && i < ac)
	{
		while (*str == ' ')
			str++;
		str = get_arg(&tab[i], str);
		i++;
	}
	tab[i] = NULL;
	return (tab);
}

char	*get_arg(char **ptr, char *str)
{
	if (*str == '\"' || *str == '\'')
	{
		*ptr = cpy_arg(str);
		str = eoa_quote(str, *str);
	}
	else if (is_ope(str))
	{
		*ptr = cpy_arg(str);
		str = end_ope(str);
	}
	else
	{
		*ptr = cpy_arg(str);
		str = eoa_str(str);
	}
	return (str);
}
