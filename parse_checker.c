/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/25 12:55:53 by bbrunell          #+#    #+#             */
/*   Updated: 2016/09/25 13:02:37 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*
**	check_str verifie si la ligne contient au début la phrase souhaite
**	avec n charactere devant la phrase comme des tabulation ("		un exemple")
**	la fonction renvoie 0 si la ligne de contient pas ce que l'on veut, sinon
**	elle renvoie le nombre de caractère verifié
*/

int		check_str(char *line, int tab, char *str, char c)
{
	char	*verif;
	int		i;
	int		j;

	i = 0;
	j = 0;
	verif = ft_strnew(tab + ft_strlen(str));
	while (i < tab)
	{
		verif[i] = c;
		i++;
	}
	while (str[j])
	{
		verif[i] = str[j];
		i++;
		j++;
	}
	if (!ft_strncmp(verif, line, ft_strlen(verif)))
		j = -1;
	free(verif);
	return ((j == -1) ? i : 0);
}

void	register_name(int a, char *line, char **name)
{
	int i;

	if (a == 0)
		ft_error(0);
	i = ft_strlen(line);
	(i - a == 0) ? ft_error(1) : 0;
	(*name) = ft_strsub(line, a, i - a);
}

void	register_type(int a, char *line, char *nbr)
{
	char	*str;

	(a == 0) ? ft_error(0) : 0;
	register_name(a, line, &str);
	if (!ft_strcmp(str, "plan"))
		*nbr = PLAN;
	else if (!ft_strcmp(str, "sphere"))
		*nbr = SPHERE;
	else if (!ft_strcmp(str, "cone"))
		*nbr = CONE;
	else if (!ft_strcmp(str, "cylindre"))
		*nbr = CYLINDRE;
	else
	{
		free(str);
		ft_error(6);
	}
	free(str);
}

/*
**	register_float recupère n float dans un tableau a partir d'une case du
**	tableau donné
**	size[0] = emplacement d'enregistrement dans le tableau
**	size[1] = nombre de case a remplir
*/

void	register_float(int a, char *line, int *size, double *nbr)
{
	char	*str;
	char	**tab;
	int		j;

	(a == 0) ? ft_error(0) : 0;
	register_name(a, line, &str);
	tab = ft_strsplit(str, ' ');
	j = 0;
	while (tab[j])
		j++;
	(j != size[1]) ? ft_error(0) : 0;
	j = 0;
	while (j < size[1])
	{
		(!verif_double(tab[j])) ? ft_error(2) : 0;
		nbr[size[0]] = ft_atod(tab[j]);
		free(tab[j]);
		j++;
		size[0]++;
	}
	free(str);
	free(tab);
}
