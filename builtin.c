/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kallegre <kallegre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 11:15:54 by kallegre          #+#    #+#             */
/*   Updated: 2023/08/29 11:15:54 by kallegre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *cmd)
{
	char	*all_cmd;
	char	**tab_cmd;
	int		i;

	if (cmd == NULL)
		return (0);
	i = 0;
	all_cmd = ft_strdup("export unset cd exit env pwd echo");
	tab_cmd = ft_split(all_cmd, ' ');
	while (tab_cmd[i])
	{
		if (ft_strncmp(tab_cmd[i], cmd, ft_strlen(cmd) + 1) == 0)
		{
			free(all_cmd);
			free_tab(tab_cmd);
			return (1);
		}
		i++;
	}
	free(all_cmd);
	free_tab(tab_cmd);
	return (0);
}

int	do_builtin(char **cmd, t_env **env, char **envp)
{
	if (!envp)
		return (0);
	if (ft_strncmp(cmd[0], "cd", ft_strlen("cd") + 1) == 0)
		return (builtin_cd(cmd, *env));
	if (ft_strncmp(cmd[0], "pwd", ft_strlen(cmd[0]) + 1) == 0)
		builtin_pwd();
	if (ft_strncmp(cmd[0], "env", ft_strlen("env") + 1) == 0)
		builtin_env(*env);
	if (ft_strncmp(cmd[0], "unset", ft_strlen(cmd[0]) + 1) == 0)
		builtin_unset(cmd, env);
	if (ft_strncmp(cmd[0], "echo", ft_strlen(cmd[0]) + 1) == 0)
		builtin_echo(cmd);
	if (ft_strncmp(cmd[0], "export", ft_strlen(cmd[0]) + 1) == 0)
		return (ft_builtin_export(cmd, env));
	if (ft_strncmp(cmd[0], "exit", ft_strlen(cmd[0]) + 1) == 0)
		return (builtin_exit(cmd));
	// return(ft_builtin_export(cmd, env));
	// ...
	return (0);
}
