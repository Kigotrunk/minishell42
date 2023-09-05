/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kallegre <kallegre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:00:37 by kortolan          #+#    #+#             */
/*   Updated: 2023/09/04 13:48:39 by kallegre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_env(t_env *env)
{
	t_env	*ptr;

	ptr = env;
	if (!ptr)
		return ;
	while (ptr)
	{
		if (ptr->print == 1 && ptr->value)
			ft_printf("%s=%s\n", ptr->name, ptr->value);
		ptr = ptr->next;
	}
}
