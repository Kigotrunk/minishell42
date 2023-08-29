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

int	builtin_cd(char **argv, t_env *env)
{
	if (argv[1] && argv[2])
	{
		print_err("cd", "too many arguments\n");
		return (1);
	}
	if (argv[1] == NULL || ft_strncmp(argv[1], "~", 2) == 0)
	{
		if (chdir(get_home_dir(env)) != 0)
		{
			perror(argv[1]);
			return (1);
		}
	}
	else if (chdir(argv[1]) != 0)
	{
		perror(argv[1]);
		return (1);
	}
	ft_change_pwd(env);
	return (0);
}

void	ft_change_pwd(t_env *env)
{
	while (env->next)
	{
		if (ft_strncmp(env->name, "PWD", ft_strlen("PWD")) == 0)
		{
			free(env->value);
			env->value = malloc(4096);
			getcwd(env->value, 4096);
			return ;
		}
		env = env->next;
	}
	if (ft_strncmp(env->name, "PWD", ft_strlen("PWD")) == 0)
	{
		free(env->value);
		env->value = malloc(4096);
		getcwd(env->value, 4096);
		return ;
	}
	ft_lstadd_back(&env, ft_lstnew("PWD", NULL, 1));
	env->next->value = malloc(4096);
	getcwd(env->next->value, 4096);
}

char	*get_home_dir(t_env *env)
{
	while (env)
	{
		if (ft_strncmp(env->name, "HOME", 5) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

void	builtin_pwd(void)
{
	char	*pwd;

	pwd = (char *)malloc(2048 * sizeof(char));
	pwd = getcwd(pwd, 2048);
	if (pwd == NULL)
		perror("path");
	else
		printf("%s\n", pwd);
}
