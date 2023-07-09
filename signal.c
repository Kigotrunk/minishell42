/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kortolan <kortolan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 15:01:50 by kortolan          #+#    #+#             */
/*   Updated: 2023/07/05 15:31:53 by kortolan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void    ft_sig(int code)
{
    if (code == SIGINT)
    {
        ft_putstr_fd("\n", 1);
        rl_replace_line("", 0);
        rl_on_new_line();
    }
}