/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 01:24:42 by marvin            #+#    #+#             */
/*   Updated: 2023/06/15 01:24:42 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env   *cpy_env(char **envp)
{
    t_env   *new_env;
    int     i;

    i = 0;
    new_env = NULL;
    while (envp[i])
    {
        ft_lstadd_back(&new_env, ft_lstnew(get_name(envp[i]), get_value(envp[i]), 1));
        i++;
    }
    //leak_test(new_env);
    return (new_env);
}

void    leak_test(t_env *lst)
{
    int i;

    i = 1;
    while (lst)
    {
        ft_printf("%i: %p\n", i, lst);
        lst = lst->next;
        i++;
    }
}