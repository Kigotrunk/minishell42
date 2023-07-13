/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kortolan <kortolan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 15:14:51 by kallegre          #+#    #+#             */
/*   Updated: 2023/07/12 22:38:44 by kortolan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*s;
	int		i;

	s = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (s == NULL)
		return (NULL);
	i = 0;
	while (*s1)
	{
		s[i] = *s1;
		s1++;
		i++;
	}
	while (*s2)
	{
		s[i] = *s2;
		s2++;
		i++;
	}
	s[i] = '\0';
	return (s);
}
