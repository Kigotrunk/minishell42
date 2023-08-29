/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kallegre <kallegre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:00:37 by kortolan          #+#    #+#             */
/*   Updated: 2023/08/29 10:59:53 by kallegre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_env(t_env *env)
{
	t_env	*ptr;

	ptr = env;
	if (!ptr)
		perror("env");
	while (ptr)
	{
		if (ptr->print == 1 && ptr->value)
			ft_printf("%s=%s\n", ptr->name, ptr->value);
		ptr = ptr->next;
	}
}
