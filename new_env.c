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

t_env	*cpy_env(char **envp)
{
	t_env	*new_env;
	char	*tmp_name;
	char	*tmp_value;
	int		path;
	int		i;

	path = 0;
	i = 0;
	new_env = NULL;
	while (envp[i])
	{
		tmp_name = get_name(envp[i]);
		if (ft_strncmp(tmp_name, "PATH", 5) == 0)
			path = 1;
		tmp_value = get_value(envp[i]);
		ft_lstadd_back(&new_env, ft_lstnew(tmp_name, tmp_value, 1));
		free(tmp_name);
		free(tmp_value);
		i++;
	}
	if (path == 0)
		exit(1);
	return (new_env);
}

int	ft_lstclear(t_env **lst, void (*del)(void*))
{
	t_env	*end;
	t_env	*a_lst;
	t_env	*n_lst;

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
	return (0);
}
