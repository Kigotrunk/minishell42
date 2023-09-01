/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kallegre <kallegre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 10:50:22 by kallegre          #+#    #+#             */
/*   Updated: 2023/08/31 12:54:12 by kallegre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*ft_lstnew(char *name, char *value, int print)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (new == NULL)
		return (NULL);
	new->name = ft_strdup(name);
	if (value == NULL)
		new->value = NULL;
	else
		new->value = ft_strdup(value);
	new->print = print;
	new->next = NULL;
	return (new);
}

void	ft_lstadd_back(t_env **lst, t_env *new)
{
	t_env	*last;

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

void	ft_lstdelone(t_env *lst, void (*del)(void*))
{
	if (lst == NULL)
		return ;
	del(lst->name);
	del(lst->value);
	free(lst);
}

t_env	*ft_lstlast(t_env *lst)
{
	while (lst != NULL && lst->next != NULL)
		lst = lst->next;
	return (lst);
}

int	ft_lstsize(t_env *lst)
{
	int	i;

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
