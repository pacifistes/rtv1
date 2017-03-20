/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/14 15:01:31 by bbrunell          #+#    #+#             */
/*   Updated: 2016/03/14 15:01:33 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		*ft_parsing(char *str)
{
	int			*tab;
	int			i;
	char		**char_to_int;

	tab = (int *)malloc(sizeof(int) * (int)ft_get_number_of_words(str, ' '));
	char_to_int = ft_strsplit(str, ' ');
	i = 0;
	while (char_to_int[i])
	{
		tab[i] = ft_atoi(char_to_int[i]);
		if (ft_verifint(char_to_int[i]) == 2147484848 || tab[i] < 1 ||
		tab[i] > 10)
			return (NULL);
		i++;
	}
	return (tab);
}
