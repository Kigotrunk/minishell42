/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kallegre <kallegre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:00:37 by kortolan          #+#    #+#             */
/*   Updated: 2023/07/09 18:45:49 by kallegre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    builtin_env(t_env *env)
{
	int		x;
	t_env	*first;

	first = env;
	x = 0;
	if (!first)
		perror("env");
	while (first)
	{
		//if(first->print == 1)
			ft_printf("%s=%s\n", first->name, first->value);
		first = first->next;
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