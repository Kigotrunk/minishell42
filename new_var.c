/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kallegre <kallegre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 13:38:22 by kallegre          #+#    #+#             */
/*   Updated: 2023/09/01 20:57:13 by kallegre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_new_var_cmd(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		if (!is_new_var(argv[i]))
			return (0);
		i++;
	}
	return (1);
}

int	get_new_var(char **argv, t_env *env)
{
	char	*name;
	char	*value;
	int		i;

	i = 0;
	while (is_new_var(argv[i]))
	{
		if (is_var(env, argv[i]))
			modif_var_value(env, argv[i]);
		else
		{
			name = get_name(argv[i]);
			value = get_value(argv[i]);
			ft_lstadd_back(&env, ft_lstnew(name, value, 0));
			free(name);
			free(value);
		}
		i++;
	}
	return (0);
}

void	modif_var_value(t_env *env, char *arg)
{
	char	*name;
	char	*value;

	name = get_name(arg);
	value = get_value(arg);
	while (env)
	{
		if (ft_strncmp(name, env->name, ft_strlen(name)) == 0)
		{
			env->value = value;
			break ;
		}
		env = env->next;
	}
	free(name);
}

int	is_new_var(char *arg)
{
	int	i;

	i = 0;
	if (arg == NULL)
		return (0);
	if (!ft_isalpha(arg[i]) && arg[i] != '_')
		return (0);
	i++;
	while (arg[i])
	{
		if (arg[i] == '=')
			return (1);
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
			return (0);
		i++;
	}
	return (0);
}
