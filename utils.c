/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kallegre <kallegre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 13:58:39 by kallegre          #+#    #+#             */
/*   Updated: 2023/08/29 10:34:28 by kallegre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_tab_env(t_env *lst)
{
	char	**env;
	char	*tmp;
	int		i;

	i = 0;
	env = (char **)malloc((ft_lstsize(lst) + 1) * sizeof(char *));
	while (lst)
	{
		tmp = ft_strjoin(lst->name, "=");
		if (lst->value == NULL)
			env[i] = tmp;
		else
		{
			env[i] = ft_strjoin(tmp, lst->value);
			free(tmp);
		}
		i++;
		lst = lst->next;
	}
	env[i] = NULL;
	return (env);
}

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	if (tab == NULL)
		return ;
	while (tab[i])
	{
		free(tab[i]);
		tab[i] = NULL;
		i++;
	}
	free(tab);
}

void	free_tab_tab(char ***tab)
{
	int	i;

	i = 0;
	if (tab == NULL)
		return ;
	while (tab[i])
	{
		free_tab(tab[i]);
		tab[i] = NULL;
		i++;
	}
	free(tab);
}

int	tab_size(char ***tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

void	print_tab(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		ft_printf("%s\n", argv[i]);
		i++;
	}
}
