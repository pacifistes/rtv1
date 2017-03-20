/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_plan.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/27 15:42:03 by bbrunell          #+#    #+#             */
/*   Updated: 2016/09/27 15:42:06 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*
**	intersectray_plan : calcul des intersections si il y en a
**	puis calcul de la normal.
*/

double	intersectray_plan(t_ray *r, t_obj *p, t_inter *i)
{
	double		dist;
	t_vector	plan_dir;
	t_vector	plan_pos;

	plan_pos = new_vector(p->pos[0], p->pos[1], p->pos[2]);
	plan_dir = vector_normalize(new_vector(p->pos[3], p->pos[4], p->pos[5]));
	dist = (vector_dot(vector_sub(plan_pos, r->start), plan_dir) /
	vector_dot(r->dir, plan_dir));
	if (dist > EPS)
	{
		r->norm = plan_dir;
		i->inter1 = dist;
		i->inter2 = i->inter1;
		r->norm = vector_normalize(r->norm);
		return (dist);
	}
	return (0);
}
