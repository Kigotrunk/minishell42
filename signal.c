/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kallegre <kallegre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 15:01:50 by kortolan          #+#    #+#             */
/*   Updated: 2023/08/24 12:30:17 by kallegre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void    ft_sig(int code)
{
    if (code == SIGINT)
    {
        ft_printf("\r\e[0;34mminishell$\e[0m            \n");
        rl_on_new_line();
        rl_replace_line("", 0);
        rl_redisplay();
    }
}