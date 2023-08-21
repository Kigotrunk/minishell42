/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kortolan <kortolan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 13:55:47 by kallegre          #+#    #+#             */
/*   Updated: 2023/06/19 18:17:36 by kortolan         ###   ########.fr       */
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
		else if (is_ope(str))
		{
			n++;
			str = end_ope(str);
		}
		else if (*str == '\"' || *str == '\'')
		{
			n++;
			str = eoa_quote(str, *str);
		}
		else
		{
			n++;
			str = eoa_str(str);
		}
	}
	return (n);
}

int arg_len(char *str)
{
	int     i;

	i = 0;
	if (*str == '\'' || *str == '\"')
		i = eoa_quote(str, *str) - str;
	else if (is_ope(str))
		i = end_ope(str) - str;
	else
		i = eoa_str(str) - str;
	//readline?
	if (str[i - 1] == '\n')
		i--;
	return (i);
}

char	*get_arg(char *str)
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
		if(*str == '\"' || *str == '\'')
		{
			tab[i] = get_arg(str);
			str = eoa_quote(str, *str);
			i++;
		}
		else if (is_ope(str))
		{
			tab[i] = get_arg(str);
			str = end_ope(str);
			i++;
		}
		else
		{
			tab[i] = get_arg(str);
			str = eoa_str(str);
			i++;
		}
	}
	tab[i] = NULL;
	return (tab);
}