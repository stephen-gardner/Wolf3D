/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 16:23:24 by sgardner          #+#    #+#             */
/*   Updated: 2018/02/12 09:24:40 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

#define ABS(x) ((x < 0) ? -x : x)

static void	draw_vert(t_map *map, t_raycast *rc)
{
	t_canvas	*cvs;
	int			y_start;
	int			y_end;
	int			y;
	int			x;

	y = 0;
	x = rc->x;
	cvs = map->cvs;
	y_start = rc->y_start;
	y_end = rc->y_end;
	while (y < y_start - 1 && y < y_end - 1)
		*(cvs->data + (cvs->x_max * y++) + x) = CEIL_COLOR;
	if (y < y_start && y < y_end)
		*(cvs->data + (cvs->x_max * y++) + x) = 0;
	while (y < y_end - 1)
	{
		*(cvs->data + (cvs->x_max * y) + x) = get_color(rc, y);
		++y;
	}
	if (y < cvs->y_max - 1)
		*(cvs->data + (cvs->x_max * y++) + x) = 0;
	while (y < cvs->y_max - 1)
		*(cvs->data + (cvs->x_max * y++) + x) = GRND_COLOR;
}

static void	init_ray(t_map *map, t_raycast *rc)
{
	t_pos	*pos;
	double	cam_x;

	pos = map->pos;
	cam_x = ((2 * rc->x) / (double)map->cvs->x_max) - 1;
	rc->rdir_x = (pos->plane_x * cam_x) + pos->dir_x;
	rc->rdir_y = (pos->plane_y * cam_x) + pos->dir_y;
	rc->dist_dx = ABS(1 / rc->rdir_x);
	rc->dist_dy = ABS(1 / rc->rdir_y);
	rc->map_x = (int)pos->loc_x;
	rc->map_y = (int)pos->loc_y;
}

static int	find_wall(t_map *map, t_raycast *rc, int step_x, int step_y)
{
	int	side;

	while (TRUE)
	{
		if (rc->side_dist_x < rc->side_dist_y)
		{
			rc->side_dist_x += rc->dist_dx;
			rc->map_x += step_x;
			side = 0;
		}
		else
		{
			rc->side_dist_y += rc->dist_dy;
			rc->map_y += step_y;
			side = 1;
		}
		if (map->arr[rc->map_y][rc->map_x] > 0)
			break ;
	}
	return (side);
}

static void	calc_wallpoints(t_map *map, t_raycast *rc, int step_x, int step_y)
{
	t_pos	*pos;
	int		line_height;
	double	perp_wall_dist;

	pos = map->pos;
	if (rc->side)
	{
		perp_wall_dist = rc->map_y - pos->loc_y + ((1 - step_y) / 2);
		perp_wall_dist /= rc->rdir_y;
	}
	else
	{
		perp_wall_dist = rc->map_x - pos->loc_x + ((1 - step_x) / 2);
		perp_wall_dist /= rc->rdir_x;
	}
	line_height = (int)(map->cvs->y_max / perp_wall_dist);
	rc->y_start = (map->cvs->y_max / 2) - (line_height / 2);
	if (rc->y_start < 0)
		rc->y_start = 0;
	rc->y_end = (map->cvs->y_max / 2) + (line_height / 2);
	if (rc->y_end >= map->cvs->y_max)
		rc->y_end = map->cvs->y_max;
}

void		raycast(t_map *map)
{
	t_raycast	rc;
	t_pos		*pos;
	int			step_x;
	int			step_y;

	rc.x = 0;
	pos = map->pos;
	while (rc.x < map->cvs->x_max)
	{
		init_ray(map, &rc);
		step_x = (rc.rdir_x < 0) ? -1 : 1;
		rc.side_dist_x = rc.dist_dx * ((rc.rdir_x < 0) ?
			pos->loc_x - rc.map_x : rc.map_x - pos->loc_x + 1.0);
		step_y = (rc.rdir_y < 0) ? -1 : 1;
		rc.side_dist_y = rc.dist_dy * ((rc.rdir_y < 0) ?
			pos->loc_y - rc.map_y : rc.map_y - pos->loc_y + 1.0);
		rc.side = find_wall(map, &rc, step_x, step_y);
		calc_wallpoints(map, &rc, step_x, step_y);
		if (rc.side)
			rc.face = (rc.rdir_y > 0) ? NORTH : SOUTH;
		else
			rc.face = (rc.rdir_x > 0) ? EAST : WEST;
		draw_vert(map, &rc);
		++rc.x;
	}
}
