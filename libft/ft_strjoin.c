/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/25 12:42:27 by bbrunell          #+#    #+#             */
/*   Updated: 2016/09/25 12:42:42 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_join(char *join, char const *s1, char const *s2)
{
	int i;
	int j;

	if (join == NULL)
		return (NULL);
	i = 0;
	while (s1 != NULL && s1[i] != '\0')
	{
		join[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2 != NULL && s2[j] != '\0')
	{
		join[i] = s2[j];
		i++;
		j++;
	}
	join[i] = '\0';
	return (join);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		j;
	char	*join;

	j = 0;
	if (s1 == NULL && s2 == NULL)
		return (NULL);
	else if (s1 == NULL)
		j = ft_strlen(s2);
	else if (s2 == NULL)
		j = ft_strlen(s1);
	else if (s1 != NULL && s2 != NULL)
		j = ft_strlen(s1) + ft_strlen(s2);
	join = (char*)malloc(sizeof(char) * (j + 1));
	return (ft_join(join, s1, s2));
}
