/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kallegre <kallegre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 11:34:06 by kallegre          #+#    #+#             */
/*   Updated: 2023/08/27 10:13:19 by kallegre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redir_err(char* ope, char *filename)
{
	int		errfile;

	if (ope[1] == '>')
		errfile = open(filename, O_APPEND | O_WRONLY | O_CREAT, 0644);
	else
		errfile = open(filename, O_TRUNC | O_WRONLY | O_CREAT, 0644);
	if (errfile == -1)
	{
		perror(filename);
		return (1);
	}
	dup2(errfile, 2);
	close(errfile);
	return (0);
}

int	redir_in(char* ope, char *filename, int **heredoc)
{
    int filein;

	if (ope[1] == '<')
	{
		*heredoc = (int *)malloc(2 * sizeof(int));
		if (get_heredoc(*heredoc, filename))
			return (1);
	}
	else
	{
		free(*heredoc);
		*heredoc = NULL;
		filein = open(filename, O_RDONLY);
		if (filein == -1)
		{
			perror(filename);
			return (1);
		}
		dup2(filein, 0);
		close(filein);
	}
	return (0);
}

int	redir_out(char* ope, char *filename)
{
    int fileout;

	if (ope[1] == '>')
		fileout = open(filename, O_APPEND | O_WRONLY | O_CREAT, 0644);
	else
		fileout = open(filename, O_TRUNC | O_WRONLY | O_CREAT, 0644);
	if (fileout == -1)
	{
		perror(filename);
		return (1);
	}
	dup2(fileout, 1);
	close(fileout);
	return (0);
}
