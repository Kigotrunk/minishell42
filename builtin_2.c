/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 01:35:58 by marvin            #+#    #+#             */
/*   Updated: 2023/06/15 01:35:58 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*void    builtin_cd(const char *path)
{
    int i;

    i = chdir(path);
    if (i == -1)
        perror("path");
}

void    builtin_pwd(char **cmd)
{
    char    *pwd;

	(void)cmd;
	if (cmd[1])
	{
		write(1, "too many arguments\n", 19);
		return ;
	}
    	pwd = (char *)malloc(2048 * sizeof(char));
    	pwd = getcwd(pwd, 2048);
    	if (pwd == NULL)
       		perror("path");
    	else
        	printf("%s\n", pwd);
}

void    builtin_env(t_env *env)
{
	int	x;

	x = 0;
	if (!env)
		perror("env");
	while (env)
	{
		printf("%s\n", *env->e);
		*env = *env->next
	}
}*/