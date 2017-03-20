/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_functions2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/25 15:25:15 by bbrunell          #+#    #+#             */
/*   Updated: 2016/09/25 15:25:17 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*
** renvoie la magnitude d'un vecteur (sa 'longueur' dans le repere orthonorme)
*/

double		vector_magnitude(t_vector v)
{
	return (sqrtf(vector_dot(v, v)));
}

/*
** renvoie les composantes normalisees d'un vecteur : [-1;1]
*/

t_vector	vector_normalize(t_vector v)
{
	t_vector	result;
	double		norm;

	norm = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	if (norm)
	{
		result.x = v.x / norm;
		result.y = v.y / norm;
		result.z = v.z / norm;
	}
	else
	{
		result.x = 0;
		result.y = 0;
		result.z = 0;
	}
	return (result);
}

/*
** cree un nouveau vecteur avec 3 variables passees en parametre
*/

t_vector	new_vector(double x, double y, double z)
{
	t_vector result;

	result.x = x;
	result.y = y;
	result.z = z;
	return (result);
}

/*
** renvoie la distance entre le point v2 et le point v1
*/

double		vector_dist(t_vector v1, t_vector v2)
{
	t_vector sub;

	sub = vector_sub(v1, v2);
	return (vector_magnitude(sub));
}

/*
** renvoie les coordonnes du point touche par le rayon qui pat de start,
** suivant dir et faisant dist de long. P = x0 + x*t
*/

t_vector	get_hitpoint(t_vector start, t_vector dir, double dist)
{
	t_vector hitpoint;

	hitpoint.x = start.x + dist * dir.x;
	hitpoint.y = start.y + dist * dir.y;
	hitpoint.z = start.z + dist * dir.z;
	return (hitpoint);
}
