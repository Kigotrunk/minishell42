/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kortolan <kortolan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 15:01:50 by kortolan          #+#    #+#             */
/*   Updated: 2023/07/14 00:36:28 by kortolan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void    ft_sig(int code)
{
    if (code == SIGINT)
    {
        ft_printf("\rminishell$   \n");
        rl_on_new_line();
        rl_replace_line("$-end_of_line", 0);
        rl_redisplay();
    }
}