/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/25 13:06:14 by bbrunell          #+#    #+#             */
/*   Updated: 2016/09/25 13:06:17 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	register_object(char **line, t_obj **tmp, int a)
{
	(a == -1) ? check_str(*line, 0, "object:", '\t') : 0;
	(a == 0) ? check_str(*line, 1, "simple_obj:", '\t') : 0;
	(a == 1) ? register_name(check_str(*line, 2, "name: ", '\t'),
	*line, &(*tmp)->name) : 0;
	(a == 2) ? register_type(check_str(*line, 2, "type: ", '\t'),
	*line, &(*tmp)->type) : 0;
	(a == 3) ? register_float(check_str(*line, 2, "pos: ", '\t'),
	*line, (int *)(int[]){0, 3}, (*tmp)->pos) : 0;
	(a == 4) ? register_float(check_str(*line, 2, "dir: ", '\t'),
	*line, (int *)(int[]){3, 3}, (*tmp)->pos) : 0;
	(a == 5) ? register_float(check_str(*line, 2, "size: ", '\t'),
	*line, (int *)(int[]){0, 3}, (*tmp)->size) : 0;
	(a == 6) ? takecolor(check_str(*line, 2, "color: ", '\t'),
	*line, &(*tmp)->c_o) : 0;
}

static void	check_object(t_obj **s, int fd, char **line)
{
	int		a;
	int		ret;
	int		i;
	t_obj	*tmp;

	a = -1;
	i = 0;
	tmp = ft_memalloc(sizeof(t_obj));
	while (do_gnl(line, fd, &ret) && ret == 1)
	{
		register_object(line, &tmp, a);
		if (a == 6)
			*s = ft_add_obj(*s, *tmp, 6, 3);
		i = (a == 6 && i == 0) ? 1 : i;
		a = (a == 6) ? 0 : a + 1;
	}
	free(tmp);
	(void)s;
	(void)fd;
	(void)line;
}

static void	check_spot_ambiance(t_scene **sc, int fd, char **line, int a)
{
	int		ret;
	int		i;
	t_spot	*tmp;

	i = 0;
	tmp = ft_memalloc(sizeof(t_spot));
	while (do_gnl(line, fd, &ret) && ret == 1)
	{
		if (!ft_strncmp("ambiance: ", *line, 10) && a == 0 && i != 0)
		{
			ambiance(check_str(*line, 0, "ambiance: ", '\t'),
			*line, (*sc)->amb);
			free(tmp);
			return ;
		}
		(a == 0) ? check_str(*line, 1, "spot:", '\t') : 0;
		(a == 1) ? register_float(check_str(*line, 2, "pos: ", '\t'),
		*line, (int *)(int[]){0, 3}, tmp->spot) : 0;
		(a == 2) ? takecolor(check_str(*line, 2, "color: ", '\t'),
		*line, &tmp->c_s) : 0;
		if (a == 2)
			ft_add_spot(&(*sc)->spot, *tmp, 3);
		i = (a == 2) ? 1 : i;
		a = (a == 2) ? 0 : a + 1;
	}
}

static void	check_camera(t_scene **s, int fd, char **line, t_scene *tmp)
{
	int a;
	int ret;

	a = 0;
	while (a != -1 && do_gnl(line, fd, &ret) && ret == 1)
	{
		(a == 0) ? register_name(check_str(*line, 1, "name: ", '\t'),
		*line, &tmp->name) : 0;
		(a == 1) ? check_str(*line, 1, "camera:", '\t') : 0;
		(a == 2) ? register_float(check_str(*line, 2, "pos: ", '\t'),
		*line, (int *)(int[]){0, 3}, tmp->cam) : 0;
		a = (a == 2) ? -1 : a + 1;
	}
	if (ret != 1)
		ft_error(0);
	tmp->next = *s;
	*s = tmp;
}

/*
**	parse_scene va recup les informations d'un fichier necessaire pour la
**	réalisation du projet
**	voir fichier .rt1
*/

void		parse_scene(t_scene **s, char *str)
{
	int		fd;
	char	*line;
	int		ret;

	fd = open(str, O_RDONLY);
	ret = get_next_line(fd, &line);
	if (ret >= 0 && !ft_strcmp("scene:", line))
	{
		check_camera(s, fd, &line, ft_memalloc(sizeof(t_scene)));
		check_spot_ambiance(s, fd, &line, 0);
		check_object(&(*s)->obj, fd, &line);
		verif_name(&(*s)->obj);
		free(line);
	}
	else
	{
		(ret < 0) ? ft_putstr("Wrong file\n") :
		ft_putstr("Scene wrong format\n");
		(ret < 0) ? 0 : free(line);
		exit(1);
	}
}
