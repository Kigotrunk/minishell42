/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kortolan <kortolan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 15:13:04 by kortolan          #+#    #+#             */
/*   Updated: 2023/07/09 14:17:02 by kortolan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    builtin_unset(char **argv)
{
    int i;
    
    if (env == NULL || argv == NULL || argv[0] == NULL)
        return ;
    i = 1;
    while (argv[i])
    {
        remove_env_var(argv[i]);
        i++;
    }
}

void    remove_env_var(char *var)
{
    t_env   *i_lst;

    i_lst = env;
    if (ft_strncmp(i_lst->str, var, ft_strlen(var)) == 0)
    {
        ft_lstdelone(env, &free);
        env = i_lst->next;
        return ;
    }
    while (i_lst->next)
    {
        if(ft_strncmp(i_lst->next->str, var, ft_strlen(var)) == 0)
        {
            ft_lstdelone(i_lst->next, &free);
            i_lst->next = i_lst->next->next;
        }
        i_lst = i_lst->next;
    }
}