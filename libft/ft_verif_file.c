/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_verif_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/25 12:43:43 by bbrunell          #+#    #+#             */
/*   Updated: 2016/09/25 12:43:48 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_verif_file(char *s1, char *s2)
{
	int i;
	int j;

	i = ft_strlen(s1);
	j = ft_strlen(s2);
	if (i <= j)
		return (0);
	while (j != 0)
	{
		if (s1[i] != s2[j])
			return (0);
		i--;
		j--;
	}
	return (1);
}
