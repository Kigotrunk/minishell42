/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kallegre <kallegre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 12:12:57 by kallegre          #+#    #+#             */
/*   Updated: 2023/09/04 12:34:20 by kallegre         ###   ########.fr       */
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
		if (is_ope(argv[i]) && is_ope(argv[i + 1]) && argv[i][0] != '|')
		{
			ft_printf("Syntax error\n");
			return (1);
		}
		i++;
	}
	if (is_ope(argv[i]))
	{
		ft_printf("Syntax error\n");
		return (1);
	}
	return (0);
}

char	*get_name(char *str)
{
	char	*name;
	int		i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (i == 0)
		return (NULL);
	name = (char *)malloc(i + 1);
	i = 0;
	while (str[i] && str[i] != '=')
	{
		name[i] = str[i];
		i++;
	}
	name[i] = '\0';
	return (name);
}

char	*get_value(char *str)
{
	char	*value;
	int		i;

	while (*str && *str != '=')
		str++;
	if (*str == '\0')
		return (NULL);
	str++;
	if (*str == '\0')
		return (ft_strdup(""));
	i = 0;
	while (str[i] != '\0' && str[i] != '\n')
		i++;
	value = (char *)malloc(i + 1);
	i = 0;
	while (str[i] != '\0' && str[i] != '\n')
	{
		value[i] = str[i];
		i++;
	}
	value[i] = '\0';
	return (value);
}

char	*ft_strjoin_free1(char *s1, char *s2)
{
	char	*new;

	if (s1 == NULL || s2 == NULL)
		return (s1);
	new = ft_strjoin(s1, s2);
	free(s1);
	return (new);
}

int	tab_size(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}
