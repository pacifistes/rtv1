/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/17 16:30:16 by bbrunell          #+#    #+#             */
/*   Updated: 2016/10/17 16:30:17 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*
**	next et prev obj recupere l'adresse d'un objet afin de pouvoir change
**	la position de l'objet sans le recherche a chaque déplacement
*/

static void	next_obj(t_gen *s)
{
	t_obj *tmp;

	tmp = s->sc->obj;
	if (s->move == NULL)
		s->move = tmp;
	else
	{
		while (tmp && ft_strcmp(tmp->name, s->move->name))
			tmp = tmp->next;
		if (tmp && tmp->next)
			s->move = tmp->next;
		else
			s->move = NULL;
	}
}

static void	prev_obj(t_gen *s)
{
	t_obj *tmp;
	t_obj *temp;

	tmp = s->sc->obj;
	temp = s->sc->obj;
	if (s->move == NULL)
	{
		while (tmp->next)
			tmp = tmp->next;
		s->move = tmp;
	}
	else
	{
		if (!ft_strcmp(tmp->name, s->move->name))
			s->move = NULL;
		else
		{
			while (tmp && ft_strcmp(tmp->name, s->move->name))
			{
				temp = tmp;
				tmp = tmp->next;
			}
			s->move = temp;
		}
	}
}

static void	key_124(t_gen *s)
{
	if (s->select == 0)
	{
		next_obj(s);
		s->cam_or_not = 0;
	}
	if (s->select == 1)
	{
		s->cam_or_not = (s->cam_or_not == 0) ? 1 : 0;
		s->move = NULL;
	}
}

static void	key_hook_continue(int keycode, t_gen *s)
{
	if ((s->move || s->cam_or_not == 1) && (keycode == 83 || keycode == 84 ||
	keycode == 86 || keycode == 87 || keycode == 89 || keycode == 91))
		(s->move) ? move_obj(s, keycode) : move_cam(s, keycode);
	else
		s->nb = 1;
}

int			key_hook(int keycode, t_gen *s)
{
	if (keycode == 53)
		exit(0);
	if (keycode == 126)
		s->select = (s->select == 0) ? 1 : 0;
	if (keycode == 125)
		s->select = (s->select == 1) ? 0 : 1;
	if (keycode == 123)
	{
		if (s->select == 0)
		{
			prev_obj(s);
			s->cam_or_not = 0;
		}
		if (s->select == 1)
		{
			s->cam_or_not = (s->cam_or_not == 0) ? 1 : 0;
			s->move = NULL;
		}
	}
	if (keycode == 124)
		key_124(s);
	key_hook_continue(keycode, s);
	raytracing(s);
	return (0);
}
