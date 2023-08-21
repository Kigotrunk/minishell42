/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kallegre <kallegre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 13:58:04 by kallegre          #+#    #+#             */
/*   Updated: 2023/06/19 13:58:16 by kallegre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int quote_check(char *str)
{
	int b;

	b = 0;
	while(*str)
	{
		if (*str == '\"' && b == 0)
			b = 1;
		else if (*str == '\'' && b == 0)
			b = -1;
		else if (*str == '\"' && b == 1)
			b = 0;
		else if (*str == '\'' && b == -1)
			b = 0;
		str++;
	}
	return (b);
}

int is_ope(char *str)
{
	if (*str == '|' || *str == '<' || *str=='>')
		return (1);
	else 
	{
		while (ft_isdigit(*str))
			str++;
		if (*str == '<' || *str == '>')
			return (1);
	}
	return (0);
}

char    *end_ope(char *str)
{
	if (str[0] == '|')
		return (str + 1);
	else if (str[0] == '<' || str[0] == '>')
	{
		if (str[0] == str[1] || str[1] == '|')
			return (str + 2);
		else
			return (str + 1);
	}
	else
	{
		while (ft_isdigit(*str))
			str++;
	}
		return (str + 1);
}

char	*eoa_quote(char *str, char c)
{
	str++;
	while (*str != c && *str != '\0')
		str++;
	if (*str == c)
		str++;
	if (*str != ' ' && *str != '\0' && !is_ope(str))
		str = eoa_str(str);
	return (str);
}

char    *eoa_str(char *str)
{
	while (*str != ' ' && *str != '\'' && *str != '\"' && *str && !is_ope(str))
		str++;
	if (*str == '\'' || *str == '\"')
		str = eoa_quote(str, *str);
	return (str);
}