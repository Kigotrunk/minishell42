/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kallegre <kallegre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 15:04:14 by kallegre          #+#    #+#             */
/*   Updated: 2023/07/09 17:01:38 by kallegre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_env  *env;

int main(int argc, char **argv, char **envp)
{
    char    *input;
    char    **args;
    int     err_code;

    (void)argc;
    (void)argv;
    env = cpy_env(envp);
    while ((input = readline("minishell$ ")))
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
        err_code = minishell(args);
        free(input);
        input = NULL;
        free_tab(args);
        args = NULL;
    }
    ft_lstclear(&env, &free);
    //system("leaks minishell");
    return (0);
}

int    minishell(char **argv)
{
    char    ***cmd_tab;
    char    **io_tab;
    int     err_code;

    if (argv == NULL)
        return (0);
    argv = get_new_var(argv);
    if (syntax_error(argv))
    {
        ft_printf("Syntax error\n");
        return (258);
    }
    cmd_tab = get_cmd_tab(argv);
    //cmd_tab = ft_fix_args(cmd_tab, env); //leak
    io_tab = get_io(argv);
    err_code = pipex(cmd_tab, io_tab);
    free_tab_tab(cmd_tab);
    free_tab(io_tab);
    return (err_code);
}