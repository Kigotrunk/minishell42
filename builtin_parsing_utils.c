/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_parsing_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kallegre <kallegre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 15:18:15 by kortolan          #+#    #+#             */
/*   Updated: 2023/08/28 12:03:51 by kallegre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void echo_s_quote(int *in)
{
	if (*in == 0)
		*in = 1;	
	else
		*in = 0;
}

void echo_d_quote(int *in)
{
	if (*in == 0)
		*in = 2;
	else
		*in = 0;
}

int	ft_is_space(char c)
{
	if (c == ' ' || c == '\n' || c == '\t' ||
	 c == '\v' || c == '\f' || c == '\r' || c == '\0')
	 	return (1);
	return (0);
}

int ft_is_quote(char c)
{
	if (c == '\'' || c == '\"')
		return 1;
	return (0);
}

char	*ft_str_add(char *str, char c)
{
	char	*new;
	int		i;
	
	new = malloc(ft_strlen(str) + 2);
	i = 0;
	while (str[i])
	{
		new[i] = str[i];
		i++;
	}
	new[i] = c;
	new[i + 1] = '\0';
	free(str);
	return (new);
}