/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   amb_and_convcolor.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/25 12:53:31 by bbrunell          #+#    #+#             */
/*   Updated: 2016/09/25 12:59:55 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static int	conv_col(char *str)
{
	int	i;
	int	nbr;
	int power;

	str = letter_maj(str);
	(str[0] == '0' && str[1] == 'X') ? 0 : ft_error(3);
	i = 7;
	power = 0;
	nbr = 0;
	while (i >= 2)
	{
		if (str[i] >= 'A' && str[i] <= 'F')
			nbr = nbr + (str[i] - 55) * pow(16, power);
		else if (str[i] >= '0' && str[i] <= '9')
			nbr = nbr + (str[i] - 48) * pow(16, power);
		else
			ft_error(3);
		i--;
		power++;
	}
	return (nbr);
}

void		takecolor(int a, char *line, int *color)
{
	int		i;
	char	*str;

	if (a == 0)
		ft_error(0);
	i = ft_strlen(line);
	str = ft_strsub(line, a, i - a);
	*color = conv_col(str);
	free(str);
}

void		ambiance(int a, char *line, double *nbr)
{
	char	*str;
	char	**tab;
	int		j;

	(a == 0) ? ft_error(0) : 0;
	register_name(a, line, &str);
	tab = ft_strsplit(str, ' ');
	j = 0;
	while (tab[j])
		j++;
	(j != 2) ? ft_error(4) : 0;
	(ft_strlen(tab[0]) == 8) ? 0 : ft_error(4);
	nbr[0] = conv_col(tab[0]);
	nbr[1] = ft_atoi(tab[1]);
	(nbr[1] > 100 || nbr[1] < 0) ? ft_error(4) : 0;
	free(str);
	free(tab[0]);
	free(tab[1]);
	free(tab);
}
