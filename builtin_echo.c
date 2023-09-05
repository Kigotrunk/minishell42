/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kallegre <kallegre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 01:34:54 by marvin            #+#    #+#             */
/*   Updated: 2023/09/05 11:29:45 by kallegre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_echo(char **argv)
{
	int	i;

	if (argv[1] == NULL)
	{
		ft_printf("\n");
		return ;
	}
	i = 1;
	while (is_n_option(argv[i]))
		i++;
	while (argv[i])
	{
		ft_printf("%s", argv[i]);
		i++;
		if (argv[i])
			ft_printf(" ");
	}
	if (!is_n_option(argv[1]))
		ft_printf("\n");
}

int	is_n_option(char *arg)
{
	int	i;

	if (arg[0] != '-' || arg[1] != 'n')
		return (0);
	i = 2;
	while (arg[i] && arg[i] == 'n')
		i++;
	if (arg[i] == '\0')
		return (1);
	return (0);
}
