/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kortolan <kortolan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 15:53:46 by kortolan          #+#    #+#             */
/*   Updated: 2023/07/05 14:33:28 by kortolan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strlen_env(char *env)
{
	int	i;
	
	i = 0;
	while (env[i] != '=')
		i++;
	return (i - 1);
}

void	ft_putstr_echo(char *str, int i)
{
	int	j;
	
	j = 0;
	while (str[j + i])
	{
		printf("%c", str[j + i]);
		j++;
	}
}

t_env  *ft_lstnew(void *str)
{
        t_env  *new;

        new = malloc(sizeof(t_env));
        if (new == NULL)
                return (NULL);
        new->str = ft_strdup(str);
        new->next = NULL;
        return (new);
}

void    ft_lstadd_back(t_env **lst, t_env *new)
{
        t_env  *last;

        if (!new || !lst)
                return ;
        if (*lst == NULL)
                *lst = new;
        else
        {
                last = ft_lstlast(*lst);
                last->next = new;
        }
}

void    ft_lstdelone(t_env *lst, void (*del)(void*))
{
        if (!lst)
                return ;
        del(lst->str);
        free(lst);
}

void    ft_lstclear(t_env **lst, void (*del)(void*))
{
        t_env  *end;
        t_env  *a_lst;
        t_env  *n_lst;

        a_lst = *lst;
        end = ft_lstlast(a_lst);
        while (a_lst != end)
        {
                n_lst = a_lst->next;
                ft_lstdelone(a_lst, del);
                a_lst = n_lst;
        }
        ft_lstdelone(a_lst, del);
        *lst = NULL;
}

t_env  *ft_lstlast(t_env *lst)
{
        while (lst != NULL && lst->next != NULL)
                lst = lst->next;
        return (lst);
}

int     ft_lstsize(t_env *lst)
{
        int     i;

        if (lst == NULL)
                return (0);
        i = 0;
        while (lst->next != NULL)
        {
                lst = lst->next;
                i++;
        }
        i++;
        return (i);
}