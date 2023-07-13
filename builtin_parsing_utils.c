/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_parsing_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kortolan <kortolan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 15:18:15 by kortolan          #+#    #+#             */
/*   Updated: 2023/07/12 21:36:26 by kortolan         ###   ########.fr       */
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
	char	*add_str;
	char	*str2;
	
	str2 = malloc(sizeof(char) * 2);
	str2[0] = c;
	str2[1] = '\0';
	if (!str)
		str = ft_strdup("");
	add_str = ft_strdup(str);
	add_str = ft_strjoin(add_str, str2);
	free(str);
	free(str2);
	return (add_str);
}