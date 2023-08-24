/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kallegre <kallegre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 15:04:14 by kallegre          #+#    #+#             */
/*   Updated: 2023/08/24 12:27:53 by kallegre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int err_code;

int main(int argc, char **argv, char **envp)
{
    t_env   *env;
    char    *input;
    char    **args;

    (void)argc;
    (void)argv;
    env = cpy_env(envp);
    err_code = 0;
    signal(SIGINT, ft_sig);
    signal(SIGQUIT, ft_sig);
    while ((input = readline("\e[0;34mminishell$ \e[0m")))
    {
        if (input == NULL)
            exit(1);
        add_history(input);
        if (quote_check(input) != 0)
        {
            free(input);
            input = NULL;
            ft_printf("Error\n");
            continue ;
        }
        args = split_args(input);
        err_code = minishell(&env, args);
        free(input);
        input = NULL;
        free_tab(args);
        args = NULL;
    }
    ft_lstclear(&env, &free);
    return (0);
}

int    minishell(t_env **env, char **argv)
{
    char    ***cmd_tab;
    char    **io_tab;

    if (argv == NULL)
        return (0);
    if (syntax_error(argv))
    {
        ft_printf("Syntax error\n");
        return (258);
    }
    cmd_tab = get_cmd_tab(argv);
    cmd_tab = ft_fix_args(cmd_tab, env); //leak
    io_tab = get_io(argv);
    err_code = pipex(env, cmd_tab, io_tab);
    free_tab_tab(cmd_tab);
    free_tab(io_tab);
    return (err_code);
}