/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kallegre <kallegre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 17:19:33 by kortolan          #+#    #+#             */
/*   Updated: 2023/08/28 12:07:26 by kallegre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int err_code;

char	**ft_fix_args(char **args, t_env **env)
{
	int	in_quote;
	int	i;
	char	*new_str;
	
	in_quote = 0;
	i = 0;
	while (args[i])
	{
		new_str = ft_str_replace(args[i], &in_quote, env);
		free(args[i]);
		args[i] = new_str;
		i++;
	}
	return (args);
}

char	*ft_str_replace(char *arg, int *in_quote, t_env **env)
{
	int	i;
	char	*new_str;
	char	*tmp;
	
	if(!env)
		return (NULL);
	i = 0;
	new_str = ft_strdup("");
	while (arg[i])
	{
		if (arg[i] != '\'' && arg[i] != '\"' && arg[i] != '$')
			new_str = ft_str_add(new_str, arg[i]);
		else if (arg[i] == '\'' && *in_quote != 2)
			echo_s_quote(in_quote);
		else if (arg[i] == '\'' && *in_quote == 2)
			new_str = ft_str_add(new_str, arg[i]);
		else if (arg[i] == '\"' && *in_quote != 1)
			echo_d_quote(in_quote);
		else if (arg[i] == '\"' && *in_quote == 1)
			new_str = ft_str_add(new_str, arg[i]);
		else if (arg[i] == '$')
		{
			tmp = ft_is_dollars(arg, *in_quote, i, env);
			if(tmp != NULL)
				new_str = ft_strjoin(new_str, tmp);
			while (!ft_is_space(arg[i + 1]) && !ft_is_quote(arg[i + 1]) && *in_quote != 1 && arg[i + 1] != '$')
				i++;
		}
		i++;
	}
	return (new_str);
}

char	*ft_is_dollars(char *arg, int in_quote, int i, t_env **env)
{
	char	*new_str;
	int	n;

	n = 0;
	if (in_quote != 1)
	{
		new_str = ft_dollars(&n, arg, i, *env);
		return (new_str);
	}
	return ("$");
}

char	*ft_itoa(int n)
{
	char	*str;
	int		k;
	int		i;

	k = n;
	i = 1;
	while (k > 9)
	{
		k /= 10;
		i++;
	}
	str = malloc(i + 1);
	str[i] = '\0';
	while (i--)
	{
		str[i] = n % 10 + '0';
		n /= 10;
	}
	return (str);
}

char	*ft_dollars(int *n, char *arg, int i, t_env *env)
{
	char	*tmp;
	char	*new_str;
	//t_env	*ptr;

	//ptr = *env;
	tmp = ft_strdup("");
	if (!arg[i + 1] || ft_is_space(arg[i + 1]) == 1 || ft_is_quote(arg[i + 1]))
		return ("$");
	if(arg[i + 1] == '$')
		return ("");
	if(arg[i + 1] == '?')
	{
		//ft_printf("%d\n", err_code);
		return (ft_itoa(err_code));
	}
	i++;
	while (arg[i])
	{
		if (!ft_is_space(arg[i]) && !ft_is_quote(arg[i]) && arg[i] != '$')
			tmp = ft_str_add(tmp, arg[i]);
		else
			break;
		i++;	
	}
	while ((env))
	{
		if(strncmp(tmp, (env)->name, ft_strlen(tmp) + 1) == 0)
		{
			if(env->value == NULL)
				return (NULL);
			new_str = ft_strdup(ft_size_var(n, env));
			free(tmp);
			return (new_str);
		}
		env = (env)->next;
	}
	if (tmp)
		free(tmp);
	return (NULL);	
}

char	*ft_size_var(int *n, t_env *env)
{
	char	*new_str;
	int	i;

	if(env->value == NULL)
		return(NULL);
	new_str = ft_strdup("");
	i = 0;
	while (env->value[i])
	{
		new_str = ft_str_add(new_str, env->value[i]);
		*n += 1;
		i++;
	}
	return (new_str);
}