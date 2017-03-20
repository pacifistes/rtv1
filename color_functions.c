/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/25 15:24:25 by bbrunell          #+#    #+#             */
/*   Updated: 2016/09/25 15:24:29 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*
**	color_composant enregistre la valeur  de r,g et b de la couleur dans
**	different double, chaque couleur sera divise par 255.
*/

void	color_composants(int color, double *ret)
{
	int r;
	int g;
	int b;

	r = (color & 0xFF0000) >> 16;
	g = (color & 0xFF00) >> 8;
	b = (color & 0xFF);
	ret[0] = (double)r / 255.0;
	ret[1] = (double)g / 255.0;
	ret[2] = (double)b / 255.0;
}

/*
**	renvoie la couleur final en assemblant les valeur rgb.
*/

int		colorfromrgb(double *rgb)
{
	int r;
	int g;
	int b;

	r = rgb[0] * 255;
	g = rgb[1] * 255;
	b = rgb[2] * 255;
	if (r > 255)
		r = 255;
	if (g > 255)
		g = 255;
	if (b > 255)
		b = 255;
	if (r < 0)
		r = 0;
	if (g < 0)
		g = 0;
	if (b < 0)
		b = 0;
	return ((r << 16) + (g << 8) + b);
}
