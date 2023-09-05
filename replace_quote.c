/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_quote.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kallegre <kallegre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 11:46:16 by kallegre          #+#    #+#             */
/*   Updated: 2023/09/04 13:42:08 by kallegre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*replace_quote(char *arg, t_env **env, int err_code)
{
	char	*new;
	int		i;

	new = ft_strdup("");
	i = 0;
	while (arg[i])
	{
		if (arg[i] == '\'' && is_in_quote(arg, i) != 2)
			i++;
		else if (arg[i] == '\"' && is_in_quote(arg, i) != 1)
			i++;
		else if (arg[i] == '$' && (ft_isalpha(arg[i + 1]) || arg[i + 1] == '_'
				|| arg[i + 1] == '?') && is_in_quote(arg, i) != 1)
		{
			i++;
			new = ft_strjoin_free1(new, get_var(arg + i, env, err_code));
			i += var_size(arg + i);
		}
		else
		{
			new = ft_str_add(new, arg[i]);
			i++;
		}
	}
	return (new);
}

int	var_size(char *str)
{
	int	i;

	i = 0;
	if (*str == '?')
		return (1);
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	return (i);
}

char	*get_var(char *str, t_env **env, int err_code)
{
	t_env	*ptr;

	if (env == NULL)
		return (NULL);
	ptr = *env;
	if (*str == '?')
		return (ft_itoa(err_code));
	while (ptr)
	{
		if (ft_strncmp(ptr->name, str, var_size(str)) == 0 
			&& ptr->name[var_size(str)] == '\0')
			return (ptr->value);
		ptr = ptr->next;
	}
	return (NULL);
}

int	is_in_quote(char *str, int index)
{
	int	i;
	int	quote;

	quote = 0;
	i = 0;
	while (i < index)
	{
		if (str[i] == '\"' && quote == 0)
			quote = 2;
		else if (str[i] == '\'' && quote == 0)
			quote = 1;
		else if (str[i] == '\"' && quote == 2)
			quote = 0;
		else if (str[i] == '\'' && quote == 1)
			quote = 0;
		i++;
	}
	return (quote);
}
