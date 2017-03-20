/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_image_put_pixel.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/25 15:24:49 by bbrunell          #+#    #+#             */
/*   Updated: 2016/09/25 15:24:53 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	mlx_image_put_pixel(t_id *g, int x, int y, int color)
{
	int	index;

	if (y >= W_Y || x >= W_X || x < 0 || y < 0)
		return ;
	index = (y * g->s_line) + x * (g->bpp);
	g->data[index + 3] = (color & 0xFF000000) >> 24;
	g->data[index + 2] = (color & 0x00FF0000) >> 16;
	g->data[index + 1] = (color & 0x0000FF00) >> 8;
	g->data[index] = color & 0x000000FF;
}
