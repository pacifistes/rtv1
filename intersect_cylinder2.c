/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cylinder2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/27 13:16:22 by bbrunell          #+#    #+#             */
/*   Updated: 2016/09/27 13:16:27 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*
**	voir fichier intersect_cylinder.c
*/

void		cyl_norm(t_ray *r, t_cylindre *cyl)
{
	t_vector	inter;
	t_vector	proj;
	t_vector	cyl_pos_dir;
	t_vector	cyl_dir2;
	double		dot[2];

	cyl_pos_dir = vector_add(cyl->pos, cyl->dir);
	cyl_dir2 = vector_sub(cyl_pos_dir, cyl->pos);
	dot[0] = vector_dot((cyl_dir2), (cyl_dir2));
	inter = vectormultby_scalar(r->dir, cyl->second.dist);
	inter = vector_add(inter, r->start);
	proj = vector_sub(inter, cyl_pos_dir);
	dot[1] = vector_dot((cyl_dir2), (proj)) / dot[0];
	cyl_dir2 = vectormultby_scalar(cyl_dir2, dot[1]);
	cyl_dir2 = vector_add(cyl_dir2, cyl_pos_dir);
	proj = cyl_dir2;
	proj = vector_sub(proj, cyl->pos);
	r->norm = inter;
	proj = vector_add(cyl->pos, proj);
	r->norm = vector_sub(r->norm, proj);
	r->norm = vector_normalize(r->norm);
}

double		cyl_touch_two_plan(t_ray *r, t_obj *s, t_cylindre *cyl, t_inter *i)
{
	if (cyl->inter_plan1 > 0 && (cyl->inter_plan1 <
	cyl->inter_plan2 || cyl->inter_plan2 < 0))
	{
		if (vector_dist(get_hitpoint(r->start, r->dir, cyl->inter_plan1),
		cyl->pos) < vector_dist(get_hitpoint(r->start, r->dir,
		cyl->inter_plan1), get_hitpoint(cyl->pos, cyl->dir, s->size[1] / 2)))
			r->norm = cyl->plan1_dir;
		else
			r->norm = cyl->dir;
		i->inter1 = cyl->inter_plan1;
		i->inter2 = cyl->inter_plan2;
		return (cyl->inter_plan1);
	}
	if (vector_dist(get_hitpoint(r->start, r->dir, cyl->inter_plan2),
	cyl->pos) < vector_dist(get_hitpoint(r->start, r->dir, cyl->inter_plan2),
	get_hitpoint(cyl->pos, cyl->dir, s->size[1] / 2)))
		r->norm = cyl->plan1_dir;
	else
		r->norm = cyl->dir;
	i->inter1 = cyl->inter_plan2;
	i->inter2 = cyl->inter_plan1;
	return (cyl->inter_plan2);
}

double		cyl_touch_one_plan(t_ray *r, t_obj *s, t_cylindre *cyl, t_inter *i)
{
	cyl->plan1_dir = vectormultby_scalar(cyl->dir, -1);
	if (cyl->dist_pos_inter1 < cyl->dist_inter1_plan)
		cyl->plan1_pos = get_hitpoint(cyl->pos, cyl->plan1_dir,
		s->size[1] / 2);
	else
		cyl->plan1_pos = get_hitpoint(cyl->pos, cyl->dir, s->size[1] / 2);
	cyl->inter_plan1 = (vector_dot(vector_sub(cyl->plan1_pos, r->start),
	cyl->plan1_dir) / vector_dot(r->dir, cyl->plan1_dir));
	i->inter1 = cyl->inter_plan1;
	if (cyl->inter_plan1 <= 0 && i->inter2 <= 0)
	{
		i->inter1 = cyl->previous_value1;
		i->inter2 = cyl->previous_value2;
		return (0);
	}
	if (vector_dist(get_hitpoint(r->start, r->dir, cyl->inter_plan1),
	cyl->pos) < vector_dist(get_hitpoint(r->start, r->dir,
	cyl->inter_plan1), get_hitpoint(cyl->pos, cyl->dir, s->size[1] / 2)))
		r->norm = cyl->plan1_dir;
	else
		r->norm = cyl->dir;
	return ((cyl->inter_plan1 <= 0) ? i->inter2 : cyl->inter_plan1);
}

double		cyl_touch_one_plan2(t_ray *r, t_obj *s, t_cylindre *cyl, t_inter *i)
{
	cyl->plan1_dir = vectormultby_scalar(cyl->dir, -1);
	if (cyl->dist_pos_inter2 < cyl->dist_inter2_plan)
		cyl->plan1_pos = get_hitpoint(cyl->pos, cyl->plan1_dir,
		s->size[1] / 2);
	else
		cyl->plan1_pos = get_hitpoint(cyl->pos, cyl->dir,
		s->size[1] / 2);
	cyl->inter_plan1 = (vector_dot(vector_sub(cyl->plan1_pos, r->start),
	cyl->plan1_dir) / vector_dot(r->dir, cyl->plan1_dir));
	if (cyl->inter_plan1 < i->inter1 && cyl->inter_plan1 > 0)
	{
		i->inter2 = i->inter1;
		i->inter1 = cyl->inter_plan1;
		if (vector_dist(get_hitpoint(r->start, r->dir, cyl->inter_plan1),
		cyl->pos) < vector_dist(get_hitpoint(r->start, r->dir,
		cyl->inter_plan1), get_hitpoint(cyl->pos, cyl->dir, s->size[1] / 2)))
			r->norm = cyl->plan1_dir;
		else
			r->norm = cyl->dir;
		return (cyl->inter_plan1);
	}
	i->inter2 = cyl->inter_plan1;
	cyl_norm(r, cyl);
	return (cyl->second.dist);
}
