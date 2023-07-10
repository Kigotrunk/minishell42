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

void    builtin_cd(char **argv)
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
    ft_change_pwd();
}

void    ft_change_pwd()
{
    t_env   *first;

    first = env;
    while (first->next)
    {
        if (!ft_strncmp(first->name, "PWD", ft_strlen("PWD")))
        {
            free(first->value);
            first->value = getcwd(first->value, 2048);
        }
        first = first->next;
    }
}
