/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kallegre <kallegre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 12:02:00 by kallegre          #+#    #+#             */
/*   Updated: 2023/08/29 11:01:35 by kallegre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_exit(char **argv)
{
	long long	var_exit;

	if (!argv[1])
		exit(0);
	if (argv[2])
	{
		print_err("exit", "too many arguments");
		return (1);
	}
	if (!is_number(argv[1]) || check_longl(argv[1]))
	{
		print_err("exit", "numeric argument required");
		exit(2);
	}
	var_exit = ft_atoi(argv[1]);
	if (var_exit > 255)
		var_exit = var_exit % 255;
	exit(var_exit);
}

int	is_number(char *arg)
{
	int	i;

	i = 0;
	if (arg[i] == '+' || arg[i] == '-')
		i++;
	while (arg[i])
	{
		if (arg[i] >= 48 && arg[i] <= 57)
			i++;
		else
			return (0);
	}
	return (1);
}

int	check_longl(char *str)
{
	int	i;

	if (ft_strncmp(str, "-9223372036854775808", 20) == 0)
		return (0);
	if (*str == '-' || *str == '+')
		str++;
	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (1);
		i++;
	}
	if (ft_strlen(str) < 19)
		return (0);
	else if (ft_strlen(str) > 19)
		return (1);
	else
	{
		if (ft_strncmp(str, "9223372036854775807", 19) > 0)
			return (1);
	}
	return (0);
}
