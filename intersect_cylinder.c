/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cylinder.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/27 13:11:10 by bbrunell          #+#    #+#             */
/*   Updated: 2016/09/27 13:11:13 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*
**	intersectray_cylinder : realisation d'une equation de second degré
**	afin de trouvé les intersections si il y en a, decoupage du cylindre,
**	verification si le rayon passe par un des plans puis calcul de la
**	normal soit des plan soit du cylindre.
*/

int		init_and_solve2nd_degree(t_ray *r, t_obj *s, t_cylindre *cyl,
t_inter *i)
{
	cyl->pos = new_vector(s->pos[0], s->pos[1], s->pos[2]);
	cyl->dir = vector_normalize(new_vector(s->pos[3], s->pos[4], s->pos[5]));
	cyl->dot = vector_dot(r->dir, cyl->dir);
	cyl->objetpos_raypos = vector_sub(r->start, cyl->pos);
	cyl->dot2 = vector_dot(cyl->objetpos_raypos, cyl->dir);
	cyl->second.a = vector_dot(vector_sub(r->dir, vectormultby_scalar(cyl->dir,
	cyl->dot)), vector_sub(r->dir, vectormultby_scalar(cyl->dir, cyl->dot)));
	cyl->second.b = 2 * vector_dot(vector_sub(r->dir,
	vectormultby_scalar(cyl->dir, cyl->dot)), vector_sub(cyl->objetpos_raypos,
	vectormultby_scalar(cyl->dir, cyl->dot2)));
	cyl->second.c = vector_dot(vector_sub(cyl->objetpos_raypos,
	vectormultby_scalar(cyl->dir, cyl->dot2)), vector_sub(cyl->objetpos_raypos,
	vectormultby_scalar(cyl->dir, cyl->dot2))) - s->size[0] * s->size[0];
	cyl->second.discriminant = cyl->second.b * cyl->second.b -
	4 * (cyl->second.a * cyl->second.c);
	cyl->previous_value1 = i->inter1;
	cyl->previous_value2 = i->inter2;
	cyl->limit_dist = sqrtf(s->size[0] * s->size[0]
	+ s->size[1] / 2 * s->size[1] / 2);
	if (cyl->second.discriminant < 0)
		return (0);
	cyl->second.dist = equa_sec(cyl->second.a, cyl->second.b,
	cyl->second.discriminant, i);
	r->norm = new_vector(0, 0, 0);
	return (1);
}

double	reset_value(t_ray *r, t_cylindre *cyl, t_inter *i)
{
	i->inter1 = cyl->previous_value1;
	i->inter2 = cyl->previous_value2;
	r->norm = vectormultby_scalar(r->norm, 0);
	return (0);
}

double	touch_nothing_or_two_plan(t_ray *r, t_obj *s, t_cylindre *cyl,
t_inter *i)
{
	if (cyl->dist_pos_inter1 >= cyl->limit_dist && cyl->dist_pos_inter2 >=
	cyl->limit_dist && ((cyl->dist_pos_inter1 <= cyl->dist_inter1_plan &&
	cyl->dist_pos_inter2 <= cyl->dist_inter2_plan) || (cyl->dist_pos_inter1 >=
	cyl->dist_inter1_plan && cyl->dist_pos_inter2 >= cyl->dist_inter2_plan)))
		return (reset_value(r, cyl, i));
	else if (cyl->dist_pos_inter1 >= cyl->limit_dist && cyl->dist_pos_inter2 >=
	cyl->limit_dist)
	{
		if (i->inter2 == i->inter1)
			return (0);
		cyl->plan1_dir = vectormultby_scalar(cyl->dir, -1);
		cyl->plan1_pos = get_hitpoint(cyl->pos, cyl->plan1_dir, s->size[1] / 2);
		cyl->inter_plan1 = (vector_dot(vector_sub(cyl->plan1_pos, r->start),
		cyl->plan1_dir) / vector_dot(r->dir, cyl->plan1_dir));
		cyl->plan1_pos = get_hitpoint(cyl->pos, cyl->dir, s->size[1] / 2);
		cyl->inter_plan2 = (vector_dot(vector_sub(cyl->plan1_pos, r->start),
		cyl->plan1_dir) / vector_dot(r->dir, cyl->plan1_dir));
		if (cyl->inter_plan1 <= 0 && cyl->inter_plan2 <= 0)
			return (reset_value(r, cyl, i));
		return (cyl_touch_two_plan(r, s, cyl, i));
	}
	return (0);
}

double	touch_two_side_cylinder(t_ray *r, t_cylindre *cyl,
t_inter *i)
{
	cyl_norm(r, cyl);
	if (i->inter1 < 0 && i->inter2 < 0)
		return (reset_value(r, cyl, i));
	if (i->inter1 > 0 && (i->inter2 <= 0 || i->inter1 < i->inter2))
		return (i->inter1);
	return (i->inter2);
}

double	intersectray_cylinder(t_ray *r, t_obj *s,
t_inter *i)
{
	t_cylindre	cyl;

	if (init_and_solve2nd_degree(r, s, &cyl, i) == 0)
		return (0);
	cyl.dist_pos_inter1 = vector_dist(get_hitpoint(r->start, r->dir, i->inter1),
	cyl.pos);
	cyl.dist_pos_inter2 = vector_dist(get_hitpoint(r->start, r->dir, i->inter2),
	cyl.pos);
	cyl.dist_inter2_plan = vector_dist(get_hitpoint(r->start, r->dir,
	i->inter2), get_hitpoint(cyl.pos, cyl.dir, s->size[1] / 2));
	cyl.dist_inter1_plan = vector_dist(get_hitpoint(r->start, r->dir,
	i->inter1), get_hitpoint(cyl.pos, cyl.dir, s->size[1] / 2));
	if (cyl.second.dist < 0)
		return (reset_value(r, &cyl, i));
	if (cyl.dist_pos_inter1 < cyl.limit_dist && cyl.dist_pos_inter2
	>= cyl.limit_dist)
		return (cyl_touch_one_plan2(r, s, &cyl, i));
	if (cyl.dist_pos_inter1 < cyl.limit_dist &&
	cyl.dist_pos_inter2 < cyl.limit_dist)
		return (touch_two_side_cylinder(r, &cyl, i));
	if (cyl.dist_pos_inter1 >= cyl.limit_dist &&
	cyl.dist_pos_inter2 < cyl.limit_dist)
		return (cyl_touch_one_plan(r, s, &cyl, i));
	return (touch_nothing_or_two_plan(r, s, &cyl, i));
}
