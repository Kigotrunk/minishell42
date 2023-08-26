/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kallegre <kallegre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 01:34:54 by marvin            #+#    #+#             */
/*   Updated: 2023/08/25 17:47:41 by kallegre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_echo(char **argv)
{
	int	i;
	
	i = 1;
	if (argv[1][0] == '-' && argv[1][1] == 'n')
		i++;
	while (argv[i])
	{
		ft_printf("%s", argv[i]);
		i++;
		if (argv[i])
			ft_printf(" ");
	}
	if (argv[1][0] != '-' && argv[1][0] != 'n')
		ft_printf("\n");
}/*

void	builtin_echo(char **argv)
{
	int	i;
	//int	j;

	i = 1;
	if (!argv[1] || argv[1] == NULL)
		return ;
	if(!ft_print_echo(argv, i))
		ft_printf("%c", '\n');
}

int	ft_print_echo(char **argv, int index)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (argv[index + 1])
    {
		if(option_n(argv[index]) && j == 0)
			i = 1;
		else
		{
        	ft_printf("%s ", argv[index]);
			j = 1;
		}
        index++;
    }
	if(j == 1)
		ft_printf("%s", argv[index]);
	else
		i = 1;
	return (i);
}

int	option_n(char *argv)
{
	int	i;

	i = 1;
	if (argv[0] != '-')
		return (0);
	while (argv[i])
	{
		if(argv[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}
*/