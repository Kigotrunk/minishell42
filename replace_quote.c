/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_quote.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kallegre <kallegre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 11:46:16 by kallegre          #+#    #+#             */
/*   Updated: 2023/08/28 11:49:57 by kallegre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	**replace_quote_argv(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		replace_quote(argv[i]);
		i++;
	}
}

char	*replace_quote(char *arg)
{
	int	i;

	while (arg[i])
	{
		if (arg[i] == '\'' || arg[i] == '\"')
	}
}