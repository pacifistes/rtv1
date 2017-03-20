/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_sphere.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/27 15:31:01 by bbrunell          #+#    #+#             */
/*   Updated: 2016/09/27 15:31:03 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*
**	intersectray_sphere : realisation d'une equation de second degré
**	afin de trouvé les intersections si il y en a puis calcul de la
**	normal.
*/

double	find_sphere_intersect(t_ray *r, t_obj *s, t_sphere *sphere, t_inter *i)
{
	sphere->second.dist = ((-sphere->second.b +
	sqrtf(sphere->second.discriminant))
	/ (2 * sphere->second.a));
	if (((-sphere->second.b - sqrtf(sphere->second.discriminant)) /
	(2 * sphere->second.a)) < (sphere->second.dist))
	{
		sphere->second.dist = ((-sphere->second.b -
		sqrtf(sphere->second.discriminant)) / (2 * sphere->second.a));
		i->inter1 = sphere->second.dist;
		i->inter2 = ((-sphere->second.b + sqrtf(sphere->second.discriminant))
		/ (2 * sphere->second.a));
	}
	else
	{
		i->inter1 = ((-sphere->second.b + sqrtf(sphere->second.discriminant))
		/ (2 * sphere->second.a));
		i->inter2 = ((-sphere->second.b - sqrtf(sphere->second.discriminant))
		/ (2 * sphere->second.a));
	}
	sphere->inter = get_hitpoint(r->start, r->dir, sphere->second.dist);
	r->norm = new_vector((sphere->inter.x - s->pos[0]) / s->size[0],
	(sphere->inter.y - s->pos[1]) / s->size[0], (sphere->inter.z - s->pos[2]) /
	s->size[0]);
	r->norm = vector_normalize(r->norm);
	return (sphere->second.dist);
}

double	intersectray_sphere(t_ray *r, t_obj *s, t_inter *i)
{
	t_sphere	sphere;

	sphere.pos = new_vector(r->start.x - s->pos[0], r->start.y -
	s->pos[1], r->start.z - s->pos[2]);
	sphere.second.a = vector_dot(r->dir, r->dir);
	sphere.second.b = 2 * vector_dot(r->dir, sphere.pos);
	sphere.second.c = vector_dot(sphere.pos, sphere.pos) -
	s->size[0] * s->size[0];
	sphere.second.discriminant = sphere.second.b * sphere.second.b - 4 *
	(sphere.second.a * sphere.second.c);
	if (sphere.second.discriminant < 0)
		return (0);
	if (((-sphere.second.b + sqrtf(sphere.second.discriminant)) /
	(2 * sphere.second.a)) <= 0 || ((-sphere.second.b -
	sqrtf(sphere.second.discriminant)) / (2 * sphere.second.a)) <= 0)
		return (0);
	return (find_sphere_intersect(r, s, &sphere, i));
}
