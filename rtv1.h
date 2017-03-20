/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/12 17:35:21 by bbrunell          #+#    #+#             */
/*   Updated: 2016/09/12 17:36:00 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# include <mlx.h>
# include "libft/libft.h"
# include <stdlib.h>
# include <fcntl.h>
# include <pthread.h>
# include <math.h>
# include <limits.h>

# define W_X 1680
# define W_Y 1050

# define PLAN		1
# define SPHERE	2
# define CONE		3
# define CYLINDRE	4

# define EPS 0.01

# define MT 16
# define THE struct s_thread

typedef struct		s_vector
{
	double				x;
	double				y;
	double				z;
}					t_vector;

/*
**	spot = position[0-2]
**	c_s =color 0xRGB
*/

typedef struct		s_spot
{
	double			spot[3];
	int				c_s;
	void			*next;
}					t_spot;

/*
**	name = nom de l'object
**	pos[6] = pos[0-2] pour la position x,y,z pos[3-5] pour la direction x,y,z
**	size[3] = valeur potentiellement utilisable pour les objets
**	c_o = color 0xRGB
*/

typedef struct		s_obj
{
	char			*name;
	char			type;
	double			pos[6];
	double			size[3];
	int				c_o;
	void			*next;
}					t_obj;

/*
**	name = nom de la scene
**	cam[0-2] = position x,y,z
**	amb[2] = amb[0] = RGB ; amb[1] = % intensité
*/

typedef struct		s_scene
{
	char			*name;
	double			cam[3];
	double			amb[2];
	t_spot			*spot;
	t_obj			*obj;
	void			*next;
}					t_scene;

/*
**	move = objet selectionne pour le deplacement
**	select = cam or object
*/

typedef struct		s_gen
{
	t_obj			*move;
	int				nb;
	int				select;
	int				cam_or_not;
	t_scene			*sc;
}					t_gen;

/*
** struct pour le rayon depart, direction
*/

typedef struct		s_ray
{
	t_vector		start;
	t_vector		dir;
	t_vector		norm;
	t_obj			*obj;
	double			inter[2];
}					t_ray;

typedef struct		s_general
{
	char			c;
	double			bpp;
	int				bit_per_pixel;
	int				s_line;
	int				endian;
	char			*data;
	void			*img;
	void			*win;
	void			*mlx;
	int				color;
	THE				*z;
}					t_id;

typedef struct		s_thread
{
	int				nb;
	int				lim[4];
	t_id			*t;
	t_gen			*s;
}					t_thread;

typedef struct		s_second_degree
{
	double			discriminant;
	double			a;
	double			b;
	double			c;
	double			dist;
}					t_second_degree;

typedef struct		s_cylindre
{
	double			previous_value1;
	double			previous_value2;
	double			dot;
	double			dot2;
	t_vector		objetpos_raypos;
	t_vector		pos;
	t_vector		dir;
	double			limit_dist;
	t_vector		plan1_pos;
	t_vector		plan2_pos;
	t_vector		plan1_dir;
	t_vector		plan2_dir;
	t_second_degree second;
	double			inter_plan1;
	double			inter_plan2;
	double			dist_pos_inter1;
	double			dist_pos_inter2;
	double			dist_inter2_plan;
	double			dist_inter1_plan;
}					t_cylindre;

typedef struct		s_cone
{
	double			previous_value1;
	double			previous_value2;
	t_second_degree	second;
	double			k;
	t_vector		pos;
	t_vector		dir;
	t_vector		x;
	t_vector		inter_pos;
	t_vector		lambda;
}					t_cone;

typedef struct		s_sphere
{
	t_vector		inter;
	t_second_degree	second;
	t_vector		pos;
}					t_sphere;

typedef struct		s_inter
{
	double inter1;
	double inter2;
}					t_inter;

typedef struct		s_color
{
	t_spot			*spot;
	t_vector		hitpoint;
	t_vector		mirror_vec_light;
	t_vector		vec_obj_eye;
	t_vector		vec_obj_light;
	t_vector		spot_pos;
	double			dot_light_norm;
	double			intensity[3];
	double			i_a[3];
	double			i_l[3];
	double			rgb[3];
	double			col;
	int				i;
}					t_color;

/*
** fonction pour les deplacement objet et camera
*/

void				move_cam(t_gen *s, int keycode);
void				move_obj(t_gen *s, int keycode);

/*
**	fonction general du parser
*/
int					do_gnl(char **line, int fd, int *ret);
void				ft_error(int a);
void				parse_scene(t_scene **s, char *str);
void				verif_name(t_obj **s);

/*
**	fonction du parser qui verifie et enregistre toute les variables
**	necessaire
*/

int					check_str(char *line, int tab, char *str, char c);
void				register_name(int a, char *line, char **name);
void				register_type(int a, char *line, char *nbr);
void				register_float(int a, char *line, int *size,
double *nbr);
void				takecolor(int a, char *line, int *color);

/*
**	fonction qui ajoute des nouveaux maillons aux listes et ajoute les valeurs
**	des variables
*/

t_obj				*ft_add_obj(t_obj *s, t_obj tmp, int i, int j);
void				ft_add_spot(t_spot **s, t_spot tmp, int i);

/*
** des fonctions de type libft
*/

int					verif_double(char *str);
double				ft_atod(char *str);

/*
** fonctions de creation de manipulation de vecteur
*/

t_vector			get_hitpoint(t_vector start, t_vector dir, double dist);
t_vector			new_vector(double x, double y, double z);
t_vector			vector_add(t_vector v1, t_vector v2);
double				vector_dist(t_vector v1, t_vector v2);
double				vector_dot(t_vector v1, t_vector v2);
double				vector_magnitude(t_vector v);
t_vector			vectormultby_scalar(t_vector v, double scalar);
t_vector			vector_normalize(t_vector v);
t_vector			vector_sub(t_vector v1, t_vector v2);

/*
**	fonction sur les couleurs rgb
*/

void				color_composants(int color, double *ret);
int					colorfromrgb(double *rgb);

/*
**	fonction d'intersection
*/

void				cyl_norm(t_ray *r, t_cylindre *cyl);
double				cyl_touch_two_plan(t_ray *r, t_obj *s, t_cylindre *cyl,
t_inter *i);
double				cyl_touch_one_plan(t_ray *r, t_obj *s, t_cylindre *cyl,
t_inter *i);
double				cyl_touch_one_plan2(t_ray *r, t_obj *s, t_cylindre *cyl,
t_inter *i);
double				equa_sec(double a, double b, double discriminant,
t_inter *i);
double				intersectray_cone(t_ray *r, t_obj *s, t_inter *i);
double				intersectray_cylinder(t_ray *r, t_obj *s, t_inter *i);
double				intersectray_plan(t_ray *r, t_obj *p, t_inter *i);
double				intersectray_sphere(t_ray *r, t_obj *s, t_inter *i);

/*
**	reste.
**	les fonction lenray cherche si il y a une interction avec un objet et
**	renvoie sa distance
*/

void				ambiance(int a, char *line, double *nbr);
void				*display(void *z);
void				do_menu(t_id *t, int x, int y);
void				init_threads(t_thread *t, t_id *t_g, t_gen *s);
int					key_hook(int keycode, t_gen	*s);
double				lenray(t_scene *sc, t_ray *r);
double				lenray_type(t_ray *r, t_obj *s, t_inter *i);
void				mlx_image_put_pixel(t_id *g, int x, int y, int color);
void				print_menu(t_id *t, t_gen *s);
void				raytracing(t_gen *s);
#endif
