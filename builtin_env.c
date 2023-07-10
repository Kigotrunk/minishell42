/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kallegre <kallegre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:00:37 by kortolan          #+#    #+#             */
/*   Updated: 2023/07/10 11:54:57 by kallegre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    builtin_env(t_env *env)
{
	int		x;
	t_env	*ptr;

	ptr = env;
	x = 0;
	if (!ptr)
		perror("env");
	while (ptr)
	{
		if(ptr->print == 1 && ptr->value)
			ft_printf("%s=%s\n", ptr->name, ptr->value);
		ptr = ptr->next;
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