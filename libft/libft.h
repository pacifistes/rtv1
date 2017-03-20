/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/29 10:31:40 by bbrunell          #+#    #+#             */
/*   Updated: 2016/10/17 16:03:31 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

# define BUFF_SIZE 32

size_t				ft_strlen(const char *s);
char				*ft_strnew(size_t size);
char				*ft_strsub(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
int					get_next_line(int const fd, char **line);
int					ft_atoi(const char *str);
int					ft_numchr(char *s2, char c);
int					ft_nbr_case(char *s1, char c);
char				**ft_strsplit(char const *s, char c);
int					ft_strcmp(const char *s1, const char *s2);
void				ft_strdel(char **as);
int					ft_check_end(char *s1);
long int			ft_verifint(const char *str);
int					*ft_parsing(char *str);
size_t				ft_get_number_of_words(char const *s, char c);
void				ft_putstr(char const *s);
int					ft_verif_file(char *s1, char *s2);
char				*ft_strstr(char const *s1, char const *s2);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
void				*ft_memalloc(size_t size);
void				ft_bzero(void *s, size_t n);
char				*letter_maj(char *str);

#endif
