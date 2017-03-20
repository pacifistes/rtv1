/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/17 16:30:22 by bbrunell          #+#    #+#             */
/*   Updated: 2016/10/17 16:30:23 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	print_menu(t_id *t, t_gen *s)
{
	int	color[3];

	color[0] = (s->select == 0) ? 0xFFFFFF : 0x808080;
	color[1] = 0xFFFFFF;
	color[2] = (s->select == 1) ? 0xFFFFFF : 0x808080;
	mlx_string_put(t->mlx, t->win, 90, 25, color[1], "POSITION ");
	mlx_string_put(t->mlx, t->win, 25, 75, color[0], "object   : ");
	mlx_string_put(t->mlx, t->win, 25, 125, color[2], "cam/none : ");
	if (s->move)
	{
		if (ft_strlen(s->move->name) > 13)
			mlx_string_put(t->mlx, t->win, 150, 75, color[0], "name too long");
		else
			mlx_string_put(t->mlx, t->win, 150, 75, color[0], s->move->name);
	}
	else
		mlx_string_put(t->mlx, t->win, 150, 75, color[0], "none");
	mlx_string_put(t->mlx, t->win, 150, 125, color[2],
	(s->cam_or_not == 0) ? "none" : "cam");
}

void	do_menu(t_id *t, int x, int y)
{
	while (x <= 300)
	{
		mlx_image_put_pixel(t, x, y, 0xFFFFFF);
		x++;
	}
	while (y >= 0)
	{
		mlx_image_put_pixel(t, x, y, 0xFFFFFF);
		y--;
	}
	x = 0;
	y = 0;
	while (y < 175)
	{
		while (x < 300)
		{
			mlx_image_put_pixel(t, x, y, 0x000000);
			x++;
		}
		x = 300;
		y++;
	}
}
