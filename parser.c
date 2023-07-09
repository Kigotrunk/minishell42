/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kallegre <kallegre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 15:01:12 by kallegre          #+#    #+#             */
/*   Updated: 2023/07/09 14:12:16 by kallegre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int     syntax_error(char **argv)
{
    int i;

    i = 0;
    if (argv[0][0] == '|')
        return (1);
    while(argv[i + 1])
    {
        if (is_ope(argv[i]) && is_ope(argv[i + 1]))
            return (1);
        i++;
    }
    if (is_ope(argv[i]))
        return (1);
    return (0);
}

int     pipe_count(char **argv)
{
    int n;
    int i;

    n = 0;
    i = 0;
    while (argv[i])
    {
        if (argv[i][0] == '|')
            n++;
        i++;
    }
    return (n);
}

int     redir_count(char **argv)
{
    int n;
    int i;

    n = 0;
    i = 0;
    while (argv[i])
    {
        if (argv[i][0] == '<' || argv[i][0] == '>')
            n++;
        i++;
    }
    return (n);
}

int     args_count(char **tab)
{
    int i;

    i = 0;
    while(tab[i] && !is_ope(tab[i]))
        i++;
    return (i);
}

char    **get_argv(char **tab)
{
    char    **argv;
    int     ac;
    int     i;

    ac = args_count(tab);
    argv = (char **)malloc((ac + 1) * sizeof(char *));
    i = 0;
    while(i < ac)
    {
        argv[i] = ft_strdup(tab[i]);
        i++;
    }
    argv[i] = NULL;
    return (argv);
}

char    ***get_cmd_tab(char **tab)
{
    char    ***cmd_tab;
    int     i;
    int     k;

    cmd_tab = cmd_tab_init(pipe_count(tab) + 2);
    i = 0;
    k = 0;
    while (tab[i])
    {
        if (tab[i][0] == '|')
            i++;
        else if (is_ope(tab[i]))
            i += 2;
        else
        {
            cmd_tab[k] = get_argv(tab + i);
            k++;
            i += args_count(tab + i);
        }
    }
    cmd_tab[k] = NULL;
    return (cmd_tab);
}

char    **get_io(char **argv)
{
    char    **io_tab;
    int     i;

    io_tab = io_init();
    i = 0;
    while (argv[i])
    {
        if (is_ope(argv[i]) && argv[i][0] != '|')
        {
            if (argv[i][0] == '<') {
                free(io_tab[0]);
                io_tab[0] = ft_strjoin(argv[i], argv[i + 1]);
            }
            if (argv[i][0] == '>') {
                free(io_tab[1]);
                io_tab[1] = ft_strjoin(argv[i], argv[i + 1]);
            }
            if (argv[i][0] == '2' && argv[i][1] == '>') {
                free(io_tab[2]);
                io_tab[2] = ft_strjoin(argv[i], argv[i + 1]);
            }
            i += 2;
        }
        else
            i++;
    }
    return (io_tab);
}

char    **io_init()
{
    char    **io_tab;
    int     i;

    io_tab = (char **)malloc(4 * sizeof(char *));
    i = 0;
    while (i < 3)
    {
        io_tab[i] = malloc(1);
        io_tab[i][0] = '\0';
        i++;
    }
    io_tab[i] = NULL;
    return (io_tab);
}

char    ***cmd_tab_init(int n)
{
    char    ***cmd_tab;
    int     i;

    cmd_tab = (char ***)malloc(n * sizeof(char **));
    i = 0;
    while(i < n)
    {
        cmd_tab[i] = NULL;
        i++;
    }
    return (cmd_tab);
}

char    *ft_stradd(char *s1, char *s2)
{
    char    *s;
    int     i;

    s = malloc(ft_strlen(s1) + ft_strlen(s2) + 2);
    if (s == NULL)
        return (NULL);
    i = 0;
    while (*s1)
    {
        s[i] = *s1;
        s1++;
        i++;
    }
    free(s1 - i);
    s[i] = ' ';
    i++;
    while (*s2)
    {
        s[i] = *s2;
        s2++;
        i++;
    }
    s[i] = '\0';
    return (s);
}