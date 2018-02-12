/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 19:44:47 by sgardner          #+#    #+#             */
/*   Updated: 2018/02/12 09:23:49 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H
# include <errno.h>
# include <math.h>
# include "libft.h"

# define ROT 0.0225
# define MOV 0.0375
# define CEIL_COLOR 0xE5E5FF;
# define GRND_COLOR 0x006400;

# define FATAL_ERROR(msg) fatal_error(msg)
# define DEFAULT_ERROR FATAL_ERROR(strerror(errno))
# define MAP_ERROR FATAL_ERROR("Map error")

typedef enum	e_keys
{
	K_A = 0,
	K_S = 1,
	K_D = 2,
	K_W = 13,
	K_SP = 49,
	K_ESC = 53,
	K_LT = 123,
	K_RT = 124,
	K_DN = 125,
	K_UP = 126
}				t_keys;

typedef enum	e_face
{
	NORTH,
	SOUTH,
	EAST,
	WEST
}				t_face;

typedef struct	s_raycast
{
	int			x;
	int			y_start;
	int			y_end;
	int			color;
	int			map_x;
	int			map_y;
	int			face;
	double		rdir_x;
	double		rdir_y;
	double		dist_dx;
	double		dist_dy;
	double		side_dist_x;
	double		side_dist_y;
	t_bool		side;
}				t_raycast;

typedef struct	s_canvas
{
	int			*data;
	void		*img;
	void		*mlx;
	void		*win;
	int			bpp;
	int			endian;
	int			lsize;
	int			x_max;
	int			y_max;
}				t_canvas;

typedef struct	s_pos
{
	double		dir_x;
	double		dir_y;
	double		loc_x;
	double		loc_y;
	double		plane_x;
	double		plane_y;
}				t_pos;

typedef struct	s_map
{
	t_canvas	*cvs;
	t_pos		*pos;
	t_bool		keys[5];
	int			**arr;
	int			*raw;
	int			x_max;
	int			y_max;
}				t_map;

/*
** load.c
*/

t_map			*load_map(char *path);

/*
** movement.c
*/

int				keydown_handler(int key, t_map *map);
int				keyup_handler(int key, t_map *map);
void			move(t_map *map, int dir);
void			turn(t_pos *pos, int dir);

/*
** raycast.c
*/

void			raycast(t_map *map);

/*
** util.c
*/

void			fatal_error(char *msg);
int				get_color(t_raycast *rc, int y);
char			**split(char *arg);
#endif
