/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lenray.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/17 16:42:03 by bbrunell          #+#    #+#             */
/*   Updated: 2016/10/17 16:42:05 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*
**	lenray_final cherche et renvoie l'objet le plus proche, la distence sera
**	enregistre dans nearest[2], lenray enregistrera ainsi l'objet trouve,
**	ainsi que sa normal et renverra la distance.
*/

double			lenray_type(t_ray *r, t_obj *s, t_inter *i)
{
	if (s->type == SPHERE)
		return (intersectray_sphere(r, s, i));
	else if (s->type == PLAN)
		return (intersectray_plan(r, s, i));
	else if (s->type == CYLINDRE)
		return (intersectray_cylinder(r, s, i));
	else if (s->type == CONE)
		return (intersectray_cone(r, s, i));
	return (0);
}

static char		replace_nearest(t_obj *s, t_ray *r, double *nearest,
t_vector *norm)
{
	(void)s;
	nearest[2] = nearest[3];
	*norm = r->norm;
	return (1);
}

static t_obj	*lenray_final(t_obj *s, t_ray *r,
double *nearest, t_vector *norm)
{
	t_inter		i;
	t_obj		*tmp;

	i.inter1 = -1;
	while (s)
	{
		r->obj = NULL;
		nearest[3] = lenray_type(r, s, &i);
		nearest[4] = i.inter1;
		nearest[5] = i.inter2;
		if ((nearest[3] < nearest[2] && nearest[3] > EPS)
		|| (nearest[2] < 0 && nearest[3] > EPS))
		{
			if (replace_nearest(s, r, nearest, norm))
				tmp = s;
		}
		s = s->next;
	}
	return (tmp);
}

double			lenray(t_scene *sc, t_ray *r)
{
	double		nearest[6];
	t_obj		*tmp;
	t_vector	norm;

	tmp = NULL;
	nearest[0] = -1;
	nearest[1] = INT_MAX;
	norm = new_vector(0, 0, 0);
	nearest[2] = -1;
	tmp = lenray_final(sc->obj, r, nearest, &norm);
	if (nearest[2] > EPS)
	{
		r->norm = norm;
		r->obj = tmp;
	}
	return (nearest[2]);
}
