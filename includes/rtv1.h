/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vprypesh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/20 17:28:40 by vprypesh          #+#    #+#             */
/*   Updated: 2018/06/20 17:28:40 by vprypesh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H
# define LEAK system("leaks --quiet RTv1")
# define WIN_WIDTH 1600
# define WIN_HEIGHT 800
# define ZERO 1e-6
# define PI 3.14
# define SPHERE 1
# define CONE 2
# define CYLINDER 3
# define PLANE 4
# define LIGHT 5
# define BUFLEN 42
# define TRUE 1
# define FALSE 0
# define SCENE_PATH "resources/figure5.txt"
# define AA 10
# define BB 11
# define CC 12
# define DD 13
# define EE 14
# define FF 15
# define SHADOW_BIAS 1e-13
# include "../libft/libft.h"
# include "../includes/SDL/SDL2.framework/Headers/SDL.h"
# include "../includes/SDL/SDL2_ttf.framework/Headers/SDL_ttf.h"
# include "../includes/SDL/SDL2_mixer.framework/Headers/SDL_mixer.h"
# include <fcntl.h>
# include <math.h>
# include <pthread.h>
# include <stdio.h>

typedef double	t_vec __attribute__((vector_size(sizeof(double)*4)));

typedef struct	s_koefs
{
	double	lamb;
	double	phong;
}				t_koef;

typedef struct	s_point3d
{
	double		x;
	double		y;
	double		z;
	double		len;
}				t_p3d;

typedef struct	s_sphere
{
	t_p3d		origin;
	double		radius;
	Uint32		color;
	t_p3d		normal;
}				t_sphere;

typedef struct	s_ray
{
	t_p3d		origin;
	t_p3d		dir;
}				t_ray;

typedef struct	s_cam
{
	t_p3d		origin;
	t_p3d		v;
	t_p3d		u;
	t_p3d		w;
}				t_cam;

typedef struct	s_plane
{
	t_p3d		origin;
	t_p3d		normal;
	Uint32		color;
}				t_plane;

typedef struct	s_light
{
	t_p3d		position;
	double		intensity;
	t_vec		color;
}				t_light;

typedef struct	s_actions
{
	Sint8		height;
	Sint8		sides;
	Sint8		dist;
	Sint8		any;
	Sint8		cam_u;
	Sint8		cam_v;
	Sint8		cam_w;
}				t_act;

typedef struct	s_cylinder
{
	t_p3d		origin;
	t_p3d		axis;
	t_p3d		end;
	double		length;
	double		radius;
	t_p3d		normal;
	t_p3d		norm;
}				t_cylinder;

typedef struct	s_cone
{
	t_p3d		vertex;
	t_p3d		axis;
	double		angle;
	t_p3d		minm;
	t_p3d		maxm;
	t_p3d		normal;
}				t_cone;

typedef struct	s_environment
{
	void				*mlx;
	void				*win;
	SDL_Surface			*img;
	t_ray				default_ray;
	t_ray				ray;
	t_vec				color;
	t_ray				back_ray;
	t_plane				plane;
	t_sphere			sphere;
	t_cam				cam;
	t_light				light;
	struct s_objects	*lights;
	void				*objects;
	char				**map;
	t_act				*actions;
	double				dist;
	double				old_dist;
	int					back_trace;
	struct s_objects	*active;
	char				*path;
	TTF_Font			*font;
}				t_env;

typedef struct	s_objects
{
	int					type;
	void				*obj;
	t_sphere			sphere;
	t_plane				plane;
	t_light				light;
	t_cylinder			cylinder;
	t_cone				cone;
	t_p3d				origin;
	t_p3d				normal;
	Uint32				radius;
	Uint32				color;
	double				(*intersect)(void *, t_ray *);
	struct s_objects	*next;
}				t_object;

t_vec			norm_color(t_vec rgb);
double			back_trace(t_env *env);
t_p3d			sphere_coords(char *str);
t_p3d			vdiv(t_p3d vec, double a);
t_p3d			vsub(t_p3d vec1, t_p3d vec2);
t_p3d			vadd(t_p3d vec1, t_p3d vec2);
t_p3d			v_norm(t_p3d vec);
t_p3d			vmult(t_p3d vec, double a);
double			distance(t_p3d vec1, t_p3d vec2);
double			dot(t_p3d vec);
double			v_len(t_p3d vec);
double			dot_product(t_p3d v1, t_p3d v2);
double			intersect_cone(void *cone, t_ray *ray);
int				img_put_pixel(t_env *env, int x, int y, int color);
void			*create_image(t_env *env);
int				clear_img(t_env *env);
int				tracer(t_env *env);
t_plane			init_plane(t_p3d o, t_p3d n, double color);
t_sphere		init_sphere(t_p3d coords, double r, double color);
t_light			init_light(double x, double y, double z, double intensity);
t_cylinder		init_cylinder(t_p3d o, t_p3d axis, double len, double rad);
t_cone			init_cone(t_p3d vertex, t_p3d axis, double angle);
double			compute_lightning(t_p3d p, t_p3d n, t_light *light, t_p3d v);
double			intersect_sphere(void *s, t_ray *ray);
double			intersect_plane(void *p, t_ray *ray);
double			intersect_cylinder(void *cylinder, t_ray *ray);
t_object		*add_object(t_object *obj, void *object,
	double (*intersect)(t_env *, void *));
t_object		*get_lights(t_object *objs);
double			test_list(t_env *env);
char			*read_scene(char *str);
Uint32			get_objects(t_env *env);
double			float_atoi(char *str);
double			calc_color(t_object *t_ob, t_object *ob, t_env *env, double t);
int				hex_atoi(char *str);
void			print_objects(t_object *objs);
Uint32			map_rgb(t_vec rgb);
t_vec			get_rgb(int color);
void			render_text(t_env *env, char *str, SDL_Rect *dst);
void			print_cam_stats(t_env *env);
void			push_object(t_env *env, t_object *new);
t_p3d			get_coords(char *str);
Uint32			get_color(char **str, Uint32 idx);
double			quadr_eq(double a, double b, double c);
void			calc_plane(t_env *env, char **str, int idx);
Uint32			calc_sphere(t_env *env, char **str, Uint32 idx);
void			calc_cone(t_env *env, char **str, Uint32 idx);
void			calc_cylinder(t_env *env, char **s, int i);
void			object_calculations(t_env *env, Uint32 i, Uint32 j);
void			calc_light(t_env *env, char **str, Uint32 idx);
int				next_physical(t_object **obj);
void			calc_cam(t_env *env, char **str, Uint32 idx);
int				valid_format(char *file_name);

#endif
