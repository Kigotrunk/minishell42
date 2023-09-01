/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kallegre <kallegre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 11:36:31 by kallegre          #+#    #+#             */
/*   Updated: 2023/08/31 11:40:12 by kallegre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_builtin_export_1(char **split, t_env **env, int code)
{
	if (split[1] && split[1][0] != '\n' && var_name(split[0]))
		ft_lstadd_back(env, ft_lstnew(split[0], split[1], 1));
	else if (var_name(split[0]))
		ft_lstadd_back(env, ft_lstnew(split[0], NULL, 1));
	else
		code = print_export_error(code, 1, split); 
	return (code);
}

int	print_export_error(int code, int id, char **split)
{
	if (id == 0)
		print_err("minishell: export: '=': not a valid identifier", NULL);
	else
		print_err("minishell: export: '?': not a valid identifier", split[1]);
	code = 1;
	return (code);
}

void	ft_builtin_export_2(char **split, t_env **env)
{
	if (split[1])
		ft_change_var(env, split[0], split[1]);
	else
		ft_change_var(env, split[0], NULL);
	return ;
}
