/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kallegre <kallegre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 11:40:37 by kallegre          #+#    #+#             */
/*   Updated: 2023/09/05 11:36:24 by kallegre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_builtin_export(char **argv, t_env **env)
{
	char	*name;
	char	*value;
	int		code;
	int		i;

	code = 0;
	i = 1;
	if (!argv[1])
		return (print_export(*env));
	while (argv[i])
	{
		name = get_name(argv[i]);
		value = get_value(argv[i]);
		if (name == NULL)
			code = print_export_error(code, 0, value);
		else if (!is_var(*env, name))
			code = ft_builtin_export_1(name, value, env, code);
		else
			ft_builtin_export_2(name, value, env);
		i++;
		free(name);
		free(value);
	}
	return (code);
}

int	ft_change_var(t_env **env, char *name, char *value)
{
	t_env	*ptr;

	ptr = *env;
	while (ptr)
	{
		if (ft_strncmp(ptr->name, name, ft_strlen(name) + 1) == 0)
		{
			if (ptr->print == 0)
				ptr->print = 1;
			if (value == NULL)
				return (1);
			free(ptr->value);
			ptr->value = ft_strdup(value);
			return (1);
		}
		ptr = ptr->next;
	}
	return (0);
}

int	print_export(t_env *env)
{
	while (env)
	{
		if (env->print == 1)
		{
			ft_printf("declare -x ");
			ft_printf("%s", env->name);
			if (env->value != NULL)
				ft_printf("=\"%s\"\n", env->value);
			else
				ft_printf("\n");
		}
		env = env->next;
	}
	return (0);
}

int	is_var(t_env *env, char *str)
{
	int		i;
	char	*tmp;

	if (str == NULL)
		return (0);
	i = 0;
	tmp = ft_strdup("");
	while (str[i] != '=' && str[i])
	{
		tmp = ft_str_add(tmp, str[i]);
		i++;
	}
	while (env)
	{
		if (!ft_strncmp(env->name, tmp, ft_strlen(tmp)))
		{
			free(tmp);
			return (1);
		}
		env = env->next;
	}
	free(tmp);
	return (0);
}

int	var_name(char *str)
{
	int	i;

	i = 0;
	if (!ft_isalpha(str[i]) && str[i] != '_')
		return (0);
	i++;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}
