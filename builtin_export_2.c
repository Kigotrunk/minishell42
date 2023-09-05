/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kallegre <kallegre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 11:36:31 by kallegre          #+#    #+#             */
/*   Updated: 2023/09/02 16:31:51 by kallegre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_builtin_export_1(char *name, char *value, t_env **env, int code)
{
	if (value && value[0] != '\n' && var_name(name))
		ft_lstadd_back(env, ft_lstnew(name, value, 1));
	else if (var_name(name))
		ft_lstadd_back(env, ft_lstnew(name, NULL, 1));
	else
		code = print_export_error(code, 1, value); 
	return (code);
}

int	print_export_error(int code, int id, char *value)
{
	if (id == 0)
		print_err("minishell: export: '=': not a valid identifier", NULL);
	else
		print_err("minishell: export: '?': not a valid identifier", value);
	code = 1;
	return (code);
}

void	ft_builtin_export_2(char *name, char *value, t_env **env)
{
	if (value)
		ft_change_var(env, name, value);
	else
		ft_change_var(env, name, NULL);
	return ;
}
