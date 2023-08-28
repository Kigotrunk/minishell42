/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 01:35:58 by marvin            #+#    #+#             */
/*   Updated: 2023/06/15 01:35:58 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_pwd(void)
{
    char	*pwd;

    pwd = (char *)malloc(2048 * sizeof(char));
    pwd = getcwd(pwd, 2048);
	if (pwd == NULL)
     		perror("path");
	else
    	printf("%s\n", pwd);
}