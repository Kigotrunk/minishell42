/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 01:23:17 by marvin            #+#    #+#             */
/*   Updated: 2023/06/15 01:23:17 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
// without MAJ : export unset exit
// with MAJ : env cd pwd echo 
// echo cd pwd export unset env exit
int is_builtin(char *cmd)
{
    char    *all_cmd;
    char    **tab_cmd;
    int     i;
    
    i = 0;
    all_cmd = ft_strdup("export unset exit env cd pwd echo");
    tab_cmd = ft_split(all_cmd, ' ');
    while (tab_cmd[i] && i <= 2)
    {
        if (ft_strncmp(tab_cmd[i], cmd, ft_strlen(cmd) + 1) == 0)
            return (1);
        i++;
    }
    cmd = ft_str_lower(cmd);
    while (tab_cmd[i])
    {
        if (ft_strncmp(tab_cmd[i], cmd, ft_strlen(cmd) + 1) == 0)
            return (1);
        i++; 
    }
    free(all_cmd);
    free_tab(tab_cmd);
    return (0);
}

int do_builtin(char **cmd, t_env **env, char **envp)
{
    if(!envp)
        return (0);
    if (ft_strncmp(cmd[0], "cd", ft_strlen("cd") + 1) == 0)
        builtin_cd(cmd, *env);
    if (ft_strncmp(cmd[0], "pwd", ft_strlen(cmd[0]) + 1) == 0 || ft_strncmp(cmd[0], "PWD", ft_strlen(cmd[0])) == 0)
        builtin_pwd(cmd);
    if (ft_strncmp(cmd[0], "env", ft_strlen("env") + 1) == 0)
        builtin_env(*env);
    if (ft_strncmp(cmd[0], "unset", ft_strlen(cmd[0]) + 1) == 0)
        builtin_unset(cmd, env);
    if (ft_strncmp(cmd[0], "echo", ft_strlen(cmd[0]) + 1) == 0)
        builtin_echo(cmd);
    if (ft_strncmp(cmd[0], "export", ft_strlen(cmd[0]) + 1) == 0)
        ft_builtin_export(cmd, env);
    // return(ft_builtin_export(cmd, env));
    // ...
    return (0);
}

char    *ft_str_lower(char *cmd)
{
    int i;

    i = 0;
    while (cmd[i])
    {
        cmd[i] = ft_tolower(cmd[i]);
        i++;
    }
    return (cmd);
}
