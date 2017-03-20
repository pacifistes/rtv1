/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/25 12:55:30 by bbrunell          #+#    #+#             */
/*   Updated: 2016/09/25 12:58:06 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	ft_error(int a)
{
	(a == 0) ? ft_putstr("Scene wrong format\n") : 0;
	(a == 1) ? ft_putstr("error of a name\n") : 0;
	(a == 2) ? ft_putstr("error of a double\n") : 0;
	(a == 3) ? ft_putstr("error of a color\n") : 0;
	(a == 4) ? ft_putstr("error at ambiance's line\n") : 0;
	(a == 5) ? ft_putstr("error malloc\n") : 0;
	(a == 6) ? ft_putstr("error of type\n") : 0;
	exit(1);
}
