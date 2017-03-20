/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atod_and_lstadd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/25 13:02:47 by bbrunell          #+#    #+#             */
/*   Updated: 2016/09/25 13:06:06 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_obj	*ft_add_obj(t_obj *s, t_obj tmp, int i, int j)
{
	t_obj		*temp;
	int			a;
	t_vector	norm;

	a = 0;
	temp = ft_memalloc(sizeof(t_obj));
	while (a < i || a < j)
	{
		if (a < j)
			temp->size[a] = tmp.size[a];
		if (a < i)
			temp->pos[a] = tmp.pos[a];
		a++;
	}
	norm = new_vector(tmp.pos[3], tmp.pos[4], tmp.pos[5]);
	norm = vector_normalize(norm);
	tmp.pos[3] = norm.x;
	tmp.pos[4] = norm.y;
	tmp.pos[5] = norm.z;
	temp->c_o = tmp.c_o;
	temp->name = tmp.name;
	temp->type = tmp.type;
	temp->next = s;
	return (temp);
}

void	ft_add_spot(t_spot **s, t_spot tmp, int i)
{
	t_spot	*temp;
	int		a;

	a = 0;
	temp = ft_memalloc(sizeof(t_spot));
	while (a < i)
	{
		temp->spot[a] = tmp.spot[a];
		a++;
	}
	temp->c_s = tmp.c_s;
	temp->next = *s;
	*s = temp;
}

int		verif_double(char *str)
{
	int i;
	int point;

	i = 0;
	point = 0;
	while (str[i] && ((str[i] >= '0' && str[i] <= '9') ||
	(str[i] == '-' && i == 0 && str[i + 1] >= '0' && str[i + 1] <= '9') ||
	(str[i] == '.' && str[i + 1] >= '0' && str[i + 1] <= '9' && point <= 1)))
	{
		point = (str[i] == '.') ? point + 1 : point;
		i++;
	}
	return ((str[i] || i > 15) ? 0 : 1);
}

double	ft_atod(char *str)
{
	int		j;
	double	nbr;
	double	coef;
	int		a;

	nbr = 0;
	coef = 1;
	a = 0;
	j = (str[0] == '-') ? 1 : 0;
	while (str[j])
	{
		nbr = (a == 0) ? nbr * 10 + str[j] - '0' :
		nbr + ((str[j] - '0') * coef);
		j++;
		if (str[j] == '.')
		{
			a = 1;
			j++;
		}
		coef = (a == 1) ? coef * 0.1 : coef;
	}
	if (str[0] == '-')
		nbr = -nbr;
	return (nbr);
}
