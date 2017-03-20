/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/23 15:08:17 by bbrunell          #+#    #+#             */
/*   Updated: 2015/11/29 10:27:30 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_atoi_suite(const char *str, int i)
{
	int j;
	int nbr;
	int coef;

	j = i + 1;
	nbr = 0;
	coef = 1;
	while (str[j] >= '0' && str[j] <= '9')
		j++;
	j--;
	while (j != i)
	{
		nbr = nbr + coef * (str[j] - '0');
		coef = coef * 10;
		j--;
	}
	if (str[j] == '-')
		nbr = -nbr;
	if (str[j] >= '0' && str[j] <= '9')
		nbr = nbr + coef * (str[j] - '0');
	return (nbr);
}

int				ft_atoi(const char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0' && (str[i] == ' ' || str[i] == '\n' || str[i] == '\v'
	|| str[i] == '\f' || str[i] == '\t' || str[i] == '\r'))
		i++;
	if ((str[i] >= '0' && str[i] <= '9') || ((str[i] == '-' || str[i] == '+')
	&& (str[i + 1] >= '0' && str[i + 1] <= '9')))
		return (ft_atoi_suite(str, i));
	return (0);
}
