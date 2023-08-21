/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kortolan <kortolan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 16:30:05 by kortolan          #+#    #+#             */
/*   Updated: 2023/07/03 16:30:05 by kortolan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    builtin_cd(char **argv, t_env *env)
{
    char    *path;

    if(!env)
        return ;
    if (!argv[1])
    {
        ft_printf("cd : need path\n");
        return ;
    }
    path = argv[1];
    if (chdir(path) != 0)
    {
        perror("path");
        return ;
    }
    ft_change_pwd(env);
}

void    ft_change_pwd(t_env *env)
{
    t_env   *ptr;

    ptr = env;
    while (ptr->next) 
    {
        if (!ft_strncmp(ptr->name, "PWD", ft_strlen("PWD")))
        {
            ptr->value = getcwd(ptr->value, 2048);
            break;
        }
        ptr = ptr->next;
    }
}