/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/12 17:36:06 by bbrunell          #+#    #+#             */
/*   Updated: 2016/09/12 17:36:17 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	init_or_clear_window(t_id *t, t_gen *s)
{
	static char c = 0;

	if (!c)
	{
		t->mlx = mlx_init();
		t->win = mlx_new_window(t->mlx, W_X, W_Y, s->sc->name);
		t->img = mlx_new_image(t->mlx, W_X, W_Y);
		t->data = mlx_get_data_addr(t->img, &(t->bit_per_pixel), &(t->s_line),
		&(t->endian));
		t->bpp = t->bit_per_pixel / 8;
		(!(t->z = ft_memalloc(sizeof(t_thread) * MT))) ? ft_error(5) : 0;
		init_threads(t->z, t, s);
		c = 1;
	}
	else if (s->nb == 0)
	{
		mlx_clear_window(t->mlx, t->win);
		ft_bzero(t->data, W_Y * t->s_line);
	}
}

void	raytracing(t_gen *s)
{
	static t_id	t;
	int			j;
	pthread_t	p[MT];

	init_or_clear_window(&t, s);
	if (s->nb == 0)
	{
		j = -1;
		while (++j < MT)
			pthread_create(&p[j], NULL, display, &t.z[j]);
		j = -1;
		while (++j < MT)
			pthread_join(p[j], NULL);
	}
	do_menu(&t, 0, 175);
	mlx_put_image_to_window(t.mlx, t.win, t.img, 0, 0);
	print_menu(&t, s);
	s->nb = 0;
	mlx_key_hook(t.win, key_hook, s);
	mlx_loop(t.mlx);
}

void	init_struct(t_gen *s)
{
	s->sc = NULL;
	s->nb = 0;
	s->move = NULL;
	s->select = 0;
	s->cam_or_not = 0;
}

int		main(int ac, char **av)
{
	t_gen	s;

	if (ac == 2 && (ft_strcmp("./rtv1", av[0]) == 0) &&
	ft_verif_file(av[1], ".rt1"))
	{
		init_struct(&s);
		parse_scene(&s.sc, av[1]);
		s.sc->amb[1] = s.sc->amb[1] / 100;
		raytracing(&s);
	}
	else
		ft_putstr("Usage :\n./rtv1 [name].rt1\n");
	return (0);
}
