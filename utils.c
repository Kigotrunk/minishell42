/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kallegre <kallegre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 13:58:39 by kallegre          #+#    #+#             */
/*   Updated: 2023/07/10 11:26:32 by kallegre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char    **get_tab_env(t_env *lst)
{
    char    **env;
    char    *tmp;
    int     i;
    
    i = 0;
    env = (char **)malloc((ft_lstsize(lst) + 1) * sizeof(char *));
    while (lst)
    {
        tmp = ft_strjoin(lst->name, "=");
        env[i] = ft_strjoin(tmp, lst->value);
        free(tmp);
        i++;
        lst = lst->next;
    }
    env[i] = NULL;
    return (env);
}

void    free_tab(char **tab)
{
        int     i;

        i = 0;
        if (tab == NULL)
            return ;
        //ft_printf("in free:\n");
        while (tab[i])
        {
                //ft_printf("%p\n", &tab[i]);
                free(tab[i]);
                tab[i] = NULL;
                i++;
        }
        free(tab);
}

void    free_tab_tab(char ***tab)
{
    int     i;

        i = 0;
        if (tab == NULL)
            return ;
        //ft_printf("in free^2:\n");
        while (tab[i])
        {
                //ft_printf("%p\n", &tab[i]);
                free_tab(tab[i]);
                tab[i] = NULL;
                i++;
        }
        free(tab);
}

int tab_size(char ***tab)
{
    int i;

    i = 0;
    while (tab[i])
        i++;
    return (i);
}

void    print_tab(char **argv)
{
    int i;

    i = 0;
    while (argv[i])
    {
        ft_printf("%s\n", argv[i]);
        i++;
    }
}