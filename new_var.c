/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kallegre <kallegre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 13:49:45 by kallegre          #+#    #+#             */
/*   Updated: 2023/08/29 11:18:34 by kallegre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_name(char *str)
{
	char	*name;
	int		i;
	

	i = 0;
	while (str[i] != '=')
		i++;
	name = (char *)malloc(i + 1);
	i = 0;
	while (str[i] != '=')
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

	while (*str != '=')
		str++;
	str++;
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

char	**get_new_var(char **argv, t_env *env)
{
	char	*name;
	char	*value;
	int		i;
	
	i = 0;
	while (is_new_var(argv[i]))
	{
		name = get_name(argv[i]);
		/*if(!var_name(name))
		{
			ft_printf("command not found\n");
			free(name);
			return NULL;
		}*/
		value = get_value(argv[i]);
		ft_lstadd_back(&env, ft_lstnew(name, value, 0));
		free(name);
		free(value);
		i++;
	}
	return (argv + i);
}

int	is_new_var(char *arg)
{
	int	i;

	i = 0;
	if (arg == NULL)
		return (0);
	while (arg[i])
	{
		if (arg[i] == '=')
			return (1);
		i++;
	}
	return (0);
}
