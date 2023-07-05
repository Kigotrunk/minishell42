/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kallegre <kallegre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 12:42:00 by kallegre          #+#    #+#             */
/*   Updated: 2023/07/05 12:50:59 by kallegre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    redir_err(t_vars va)
{
	int		errfile;

	if (va.io_lst[2][0])
	{
		unlink(end_ope(va.io_lst[2]));
		errfile = open(end_ope(va.io_lst[2]), O_WRONLY | O_CREAT, 0666);
		dup2(errfile, 2);
		close(errfile);
	}
}

void    redir_input(t_vars va, int k)
{
    int filein;

    if (k == 0 && va.io_lst[0][0])
	{
		filein = open(end_ope(va.io_lst[0]), O_RDONLY);
		dup2(filein, 0);
		close(filein);
	}
    if (k != 0)
		dup2(va.fd[k - 1][0], 0);
}

void    redir_output(t_vars va, int k)
{
    int fileout;

    if (k == va.n - 1 && va.io_lst[1][0])
	{
		unlink(end_ope(va.io_lst[1]));
		fileout = open(end_ope(va.io_lst[1]), O_WRONLY | O_CREAT, 0666);
		dup2(fileout, 1);
		close(fileout);
	}
    if (k != va.n - 1)
		dup2(va.fd[k][1], 1);
}