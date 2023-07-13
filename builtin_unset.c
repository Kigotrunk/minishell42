/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kortolan <kortolan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 15:13:04 by kortolan          #+#    #+#             */
/*   Updated: 2023/07/12 18:04:15 by kortolan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    builtin_unset(char **argv, t_env **env)
{
    int i;
    
    if (env == NULL || argv == NULL || argv[0] == NULL)
        return ;
    i = 1;
    while (argv[i])
    {
        remove_env_var(env, argv[i]);
        i++;
    }
}

void    remove_env_var(t_env **env, char *var)
{
    t_env   *i_lst;

    i_lst = *env;
    if (ft_strncmp(i_lst->name, var, ft_strlen(var) + 1) == 0)
    {
        ft_lstdelone(*env, &free);
        *env = i_lst->next;
        return ;
    }
    while (i_lst->next)
    {
        if(ft_strncmp(i_lst->next->name, var, ft_strlen(var) + 1) == 0)
        {
            ft_lstdelone(i_lst->next, &free);
            i_lst->next = i_lst->next->next;
        }
        i_lst = i_lst->next;
    }
}