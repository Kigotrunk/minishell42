/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kallegre <kallegre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 09:29:47 by kallegre          #+#    #+#             */
/*   Updated: 2023/09/02 11:04:23 by kallegre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_str_add(char *str, char c)
{
	char	*new;
	int		i;

	new = malloc(ft_strlen(str) + 2);
	i = 0;
	while (str[i])
	{
		new[i] = str[i];
		i++;
	}
	new[i] = c;
	new[i + 1] = '\0';
	free(str);
	return (new);
}

void	print_err(char *str, char *var)
{
	while (*str)
	{
		if (*str == '?')
			write(2, var, ft_strlen(var));
		else
			write(2, str, 1);
		str++;
	}
	write(2, "\n", 1);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		k;
	int		i;

	k = n;
	i = 1;
	while (k > 9)
	{
		k /= 10;
		i++;
	}
	str = malloc(i + 1);
	str[i] = '\0';
	while (i--)
	{
		str[i] = n % 10 + '0';
		n /= 10;
	}
	return (str);
}

void	fd_back(int fd[])
{
	dup2(fd[0], 0);
	dup2(fd[1], 1);
	dup2(fd[2], 2);
	close(fd[0]);
	close(fd[1]);
	close(fd[2]);
}

void	fd_save(int fd[])
{
	fd[0] = dup(0);
	fd[1] = dup(1);
	fd[2] = dup(2);
}
