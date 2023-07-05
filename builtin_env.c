/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kortolan <kortolan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:00:37 by kortolan          #+#    #+#             */
/*   Updated: 2023/07/05 10:02:28 by kortolan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    builtin_env(t_env *env)
{
	int	x;

	x = 0;
	if (!env)
		perror("env");
	while (env)
	{
		if(var_with_value(env->str))
			ft_printf("%s\n", env->str);
		env = env->next;
	}
}

int	var_with_value(char *str)
{
	int	i;

	i = 0;
	while(str[i] != '=')
		i++;
	if(str[i])
		return(1);
	return (0);
}