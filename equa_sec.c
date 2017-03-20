/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   equa_sec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/17 17:14:02 by bbrunell          #+#    #+#             */
/*   Updated: 2016/10/17 17:14:04 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double	equa_sec(double a, double b, double discriminant, t_inter *i)
{
	if (discriminant == 0)
	{
		i->inter2 = ((-b + sqrtf(discriminant)) / (2 * a));
		i->inter1 = ((-b + sqrtf(discriminant)) / (2 * a));
		return (i->inter1);
	}
	else
	{
		i->inter1 = ((-b + sqrtf(discriminant)) / (2 * a));
		i->inter2 = ((-b - sqrtf(discriminant)) / (2 * a));
		if (i->inter2 > 0 && (i->inter2 < i->inter1 || i->inter1 < 0))
		{
			discriminant = i->inter2;
			i->inter2 = i->inter1;
			i->inter1 = discriminant;
		}
		if (i->inter1 >= 0)
			return (i->inter1);
		return (0);
	}
}
