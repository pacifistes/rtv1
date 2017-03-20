/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_gnl_and_verif_name.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/17 18:31:48 by bbrunell          #+#    #+#             */
/*   Updated: 2016/10/17 18:31:50 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*
**	verif si les objets ont tous un nom different
*/

void	verif_name(t_obj **s)
{
	t_obj	*tmp;
	t_obj	*temp;

	tmp = *s;
	while (tmp)
	{
		temp = tmp->next;
		while (temp)
		{
			if (!ft_strcmp(temp->name, tmp->name))
				ft_error(1);
			temp = temp->next;
		}
		tmp = tmp->next;
	}
}

/*
** free la line precedente et enregistre la line suivante du fichier
*/

int		do_gnl(char **line, int fd, int *ret)
{
	ft_strdel(line);
	*ret = get_next_line(fd, line);
	return (1);
}
