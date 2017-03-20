/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_functions1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/25 15:08:49 by bbrunell          #+#    #+#             */
/*   Updated: 2016/09/25 15:08:52 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*
**	retourne le cosinus de l'angle entre le v2 et le v1
*/

double		vector_dot(t_vector v1, t_vector v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

/*
**	ajoute les composantes du vecteur 1 a celles du vecteur 2
*/

t_vector	vector_add(t_vector v1, t_vector v2)
{
	t_vector result;

	result = new_vector(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
	return (result);
}

/*
**	multiplie les composante du vecteur 1 par un nombre reel
*/

t_vector	vectormultby_scalar(t_vector v, double scalar)
{
	t_vector result;

	result = new_vector(v.x * scalar, v.y * scalar, v.z * scalar);
	return (result);
}

/*
**	soustrait les composantes du vecteur 2 a celles du vecteur 1
*/

t_vector	vector_sub(t_vector v1, t_vector v2)
{
	t_vector result;

	result = new_vector(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
	return (result);
}
