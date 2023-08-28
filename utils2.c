/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kallegre <kallegre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 10:05:23 by kallegre          #+#    #+#             */
/*   Updated: 2023/08/27 10:12:07 by kallegre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_err(char *name, char *str)
{
	int	save_fd;
	
	save_fd = dup(1);
	dup2(2, 1);
	printf("minishell: %s: %s\n", name, str);
	dup2(save_fd, 1);
	close(save_fd);
}