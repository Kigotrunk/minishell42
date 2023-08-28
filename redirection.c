/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kallegre <kallegre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 12:42:00 by kallegre          #+#    #+#             */
/*   Updated: 2023/08/27 08:59:23 by kallegre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_heredoc(int* heredoc, char *delimiter)
{
	char	*line;

	if (pipe(heredoc) == -1)
		return (1);
	while (1)
	{
		write(1, "> ", 2);
		line = get_next_line(0);
		if (ft_strncmp(delimiter, line, ft_strlen(delimiter)) == 0
			&& line[ft_strlen(delimiter)] == '\n')
			break ;
		write(heredoc[1], line, ft_strlen(line));
		free(line);
	}
	close(heredoc[1]);
	return (0);
}
/*
void	redir_err(t_vars va)
{
	int		errfile;

	if (va.io_lst[2][0])
	{
		if (va.io_lst[1][2] == '>')
			errfile = open(end_ope(va.io_lst[2]), O_APPEND | O_WRONLY | O_CREAT, 0644);
		else
			errfile = open(end_ope(va.io_lst[2]), O_TRUNC | O_WRONLY | O_CREAT, 0644);
		if (errfile == -1)
		{
			perror(end_ope(va.io_lst[2]));
			exit(1);
		}
		dup2(errfile, 2);
		close(errfile);
	}
}

void	redir_input(t_vars va, int k)
{
    int filein;

    if (k == 0 && va.io_lst[0][0])
	{
		if (va.io_lst[0][1] == '<')
		{
			dup2(va.heredoc[0], 0);
			close(va.heredoc[0]);
		}
		else
		{
			filein = open(end_ope(va.io_lst[0]), O_RDONLY);
			if (filein == -1)
			{
				perror(end_ope(va.io_lst[0]));
				exit(1);
			}
			dup2(filein, 0);
			close(filein);
		}
	}
    if (k != 0)
		dup2(va.fd[k - 1][0], 0);
}

void	redir_output(t_vars va, int k)
{
    int fileout;

    if (k == va.n - 1 && va.io_lst[1][0])
	{
		if (va.io_lst[1][1] == '>')
			fileout = open(end_ope(va.io_lst[1]), O_APPEND | O_WRONLY | O_CREAT, 0644);
		else
			fileout = open(end_ope(va.io_lst[1]), O_TRUNC | O_WRONLY | O_CREAT, 0644);
		if (fileout == -1)
		{
			perror(end_ope(va.io_lst[1]));
			exit(1);
		}
		dup2(fileout, 1);
		close(fileout);
	}
    if (k != va.n - 1)
		dup2(va.fd[k][1], 1);
}
*/