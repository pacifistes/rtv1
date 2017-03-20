/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 18:28:41 by bbrunell          #+#    #+#             */
/*   Updated: 2016/11/09 18:28:45 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	move_obj(t_gen *s, int keycode)
{
	int n;

	n = 0;
	if (keycode == 83)
		s->move->pos[n] = s->move->pos[n] - 2;
	if (keycode == 84)
		s->move->pos[n] = s->move->pos[n] + 2;
	if (keycode == 86)
		s->move->pos[n + 1] = s->move->pos[n + 1] - 2;
	if (keycode == 87)
		s->move->pos[n + 1] = s->move->pos[n + 1] + 2;
	if (keycode == 89)
		s->move->pos[n + 2] = s->move->pos[n + 2] - 2;
	if (keycode == 91)
		s->move->pos[n + 2] = s->move->pos[n + 2] + 2;
}

void	move_cam(t_gen *s, int keycode)
{
	int n;

	n = 0;
	if (keycode == 83)
		s->sc->cam[n] = s->sc->cam[n] - 2;
	if (keycode == 84)
		s->sc->cam[n] = s->sc->cam[n] + 2;
	if (keycode == 86)
		s->sc->cam[n + 1] = s->sc->cam[n + 1] - 2;
	if (keycode == 87)
		s->sc->cam[n + 1] = s->sc->cam[n + 1] + 2;
	if (keycode == 89)
		s->sc->cam[n + 2] = s->sc->cam[n + 2] - 2;
	if (keycode == 91)
		s->sc->cam[n + 2] = s->sc->cam[n + 2] + 2;
}
