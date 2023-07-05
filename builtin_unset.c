/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kortolan <kortolan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 15:13:04 by kortolan          #+#    #+#             */
/*   Updated: 2023/07/05 14:54:51 by kortolan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env *builtin_unset(t_env *env, char **argv)
{
    int i;
    
    if (env == NULL || argv[0] == NULL || argv == NULL)
        return env;

    i = 1;
    while (argv[i])
    {
        env = remove_env_var(env, argv[i]);
        i++;
    }
    builtin_env(env);
    return env;
}

t_env *remove_env_var(t_env *env, char *var)
{
	char *str;

    str = ft_strjoin(var, "=");
    env = remove_first(env, str);
    env = remove_next(env, str);
    free(str);

    return env;
}

t_env *remove_first(t_env *env, char *str)
{
	t_env	*next;

    if (!strncmp(env->str, str, ft_strlen(str)))
    {
        next = env->next;
        free(env->str);
        free(env);
        env = next;
    }
    return env;
}

t_env *remove_next(t_env *env, char *str)
{
	t_env *current;
	t_env *delete;

    current = env;
    while (current->next)
    {
        if (!strncmp(current->next->str, str, ft_strlen(str)))
        {
            delete = current->next;
            current->next = delete->next;
            free(delete->str);
            free(delete);
            break;
        }
        current = current->next;
    }
    return env;
}