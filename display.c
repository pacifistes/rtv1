/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/17 17:14:11 by bbrunell          #+#    #+#             */
/*   Updated: 2016/10/17 17:14:13 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static int		ft_shadow(t_obj *s, t_color *c)
{
	t_ray	r;
	double	dist[2];
	t_inter	i;

	r.start = new_vector(c->spot_pos.x, c->spot_pos.y, c->spot_pos.z);
	dist[0] = vector_dist(r.start, c->hitpoint);
	r.dir = vector_normalize(vector_sub(c->hitpoint, c->spot_pos));
	while (s)
	{
		dist[1] = lenray_type(&r, s, &i);
		if (dist[1] > EPS && dist[1] < dist[0] - EPS)
			return (1);
		s = s->next;
	}
	return (0);
}

static double	diffuse_shadow_specular(t_ray *r, t_color *c, t_scene *sc,
t_obj *tmp)
{
	double speculaire;
	double obj_dotn;

	speculaire = 1;
	c->spot_pos = new_vector(c->spot->spot[0], c->spot->spot[1],
	c->spot->spot[2]);
	color_composants(c->spot->c_s, c->i_l);
	c->vec_obj_light = vector_normalize(vector_sub(c->spot_pos, c->hitpoint));
	c->dot_light_norm = vector_dot(c->vec_obj_light, r->norm);
	c->i_l[c->i] = (ft_shadow(sc->obj, c) == 0) ? c->i_l[c->i] : 0;
	if (vector_dot(r->norm, vector_normalize(vector_sub(c->hitpoint,
	c->spot_pos))) > 0 && tmp->type == PLAN)
		return (0);
	c->dot_light_norm = (c->dot_light_norm > 0 && c->dot_light_norm <= 90)
	? c->dot_light_norm : 0;
	c->mirror_vec_light = vector_normalize(vector_sub(vectormultby_scalar(
	r->norm, 2 * vector_dot(r->norm, c->vec_obj_light)), c->vec_obj_light));
	obj_dotn = vector_dot(r->norm, c->vec_obj_light);
	c->i_l[c->i] = (obj_dotn > 0 && obj_dotn <= 90) ? c->i_l[c->i] : 0;
	speculaire = vector_dot(c->mirror_vec_light, c->vec_obj_eye);
	speculaire = (speculaire > 0 && speculaire <= 90) ? speculaire : 0;
	return (c->i_l[c->i] = 0 ? 0 : c->i_l[c->i] * (c->rgb[c->i] *
	c->dot_light_norm + 1 * c->rgb[c->i] * pow(speculaire, 100)));
}

/*
**	calcul de la couleur ambiante, de la diffuse, de la speculaire et des
**	ombres portée. voir pour plus d'info sur la couleur :
**	http://morpheo.inrialpes.fr/people/Boyer/Teaching/Master/c7.pdf
*/

static int		find_color(t_scene *sc, t_ray *r, t_obj *tmp, double nearest)
{
	t_color	c;

	color_composants(tmp->c_o, c.rgb);
	color_composants(sc->amb[0], c.i_a);
	c.hitpoint = get_hitpoint(r->start, r->dir, nearest);
	c.vec_obj_eye = vector_normalize(vector_sub(r->start, c.hitpoint));
	if (tmp->type == PLAN && vector_dot(c.vec_obj_eye, r->norm) < 0)
		r->norm = vectormultby_scalar(r->norm, -1);
	c.i = 0;
	while (c.i < 3)
	{
		c.spot = sc->spot;
		c.col = 0;
		while (c.spot)
		{
			c.col = c.col + diffuse_shadow_specular(r, &c, sc, tmp);
			c.spot = c.spot->next;
		}
		c.intensity[c.i] = sc->amb[1] * c.rgb[c.i] * c.i_a[c.i] + c.col;
		c.i++;
	}
	return (colorfromrgb(c.intensity));
}

static double	getnearesthit(t_ray *r, t_scene *sc, double *inter,
t_id *g)
{
	double	new_nearest;
	int		color;

	r->dir = vector_normalize(new_vector(inter[0] - W_X / 2.0, W_Y / 2.0 -
	inter[1], (W_Y / 2.0) / tan(70 * 0.5)));
	new_nearest = lenray(sc, r);
	color = 0;
	if (new_nearest >= 0)
	{
		color = find_color(sc, r, r->obj, new_nearest);
		mlx_image_put_pixel(g, inter[0], inter[1], color);
	}
	return (new_nearest);
}

void			*display(void *z)
{
	t_obj		*tmp;
	t_id		*t;
	t_thread	*mt;
	t_ray		r;
	int			x_y[2];

	mt = (t_thread*)z;
	r.start = new_vector(mt->s->sc->cam[0], mt->s->sc->cam[1],
	mt->s->sc->cam[2]);
	tmp = mt->s->sc->obj;
	t = mt->t;
	x_y[1] = mt->lim[1] - 1;
	while (++x_y[1] < mt->lim[3])
	{
		x_y[0] = mt->lim[0] - 1;
		while (++x_y[0] < mt->lim[2])
			getnearesthit(&r, mt->s->sc, (double *)(double[]){x_y[0],
			x_y[1]}, t);
	}
	return (NULL);
}
