/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cone.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/27 14:21:20 by bbrunell          #+#    #+#             */
/*   Updated: 2016/09/27 14:21:22 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*
**	intersectray_cone : realisation d'une equation de second degré
**	afin de trouvé les intersections si il y en a puis calcul de la
**	normal.
*/

static double	find_inter_cone(t_ray *r, t_inter *i, t_cone *cone)
{
	if (cone->second.discriminant < 0)
		return (0);
	cone->previous_value1 = i->inter1;
	cone->previous_value2 = i->inter2;
	cone->second.dist = equa_sec(cone->second.a, cone->second.b,
	cone->second.discriminant, i);
	if (cone->second.dist < 0)
	{
		i->inter1 = cone->previous_value1;
		i->inter2 = cone->previous_value2;
		return (0);
	}
	cone->inter_pos = get_hitpoint(r->start, r->dir, cone->second.dist);
	cone->lambda = vector_normalize(vector_sub(cone->pos, cone->inter_pos));
	r->norm = vector_normalize(vector_sub(vectormultby_scalar(cone->dir,
	vector_dot(cone->lambda, cone->dir) / vector_dot(cone->dir, cone->dir)),
	cone->lambda));
	return (cone->second.dist);
}

double			intersectray_cone(t_ray *r, t_obj *s, t_inter *i)
{
	t_cone cone;

	cone.pos = new_vector(s->pos[0], s->pos[1], s->pos[2]);
	cone.dir = vector_normalize(new_vector(s->pos[3], s->pos[4], s->pos[5]));
	cone.x = vector_sub(r->start, cone.pos);
	cone.k = tan(((s->size[1] > 150) ? 150 * (M_PI / 180) / 2 : s->size[1]) *
	(M_PI / 180) / 2);
	cone.second.a = vector_dot(r->dir, r->dir) - (1 + cone.k * cone.k)
	* vector_dot(r->dir, cone.dir) * vector_dot(r->dir, cone.dir);
	cone.second.b = 2 * (vector_dot(r->dir, cone.x) - (1 + cone.k * cone.k) *
	vector_dot(r->dir, cone.dir) * vector_dot(cone.x, cone.dir));
	cone.second.c = vector_dot(cone.x, cone.x) - (1 + cone.k * cone.k) *
	vector_dot(cone.x, cone.dir) * vector_dot(cone.x, cone.dir);
	cone.second.discriminant = cone.second.b * cone.second.b - 4.0 *
	(cone.second.a * cone.second.c);
	return (find_inter_cone(r, i, &cone));
}
