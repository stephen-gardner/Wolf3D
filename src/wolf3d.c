/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 21:07:24 by sgardner          #+#    #+#             */
/*   Updated: 2018/02/12 09:05:49 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "mlx.h"
#include "wolf3d.h"

static int	close_window(t_map *map)
{
	UNUSED(map);
	exit(0);
	return (0);
}

static void	init_canvas(t_canvas *cvs, int width, int height)
{
	cvs->x_max = width;
	cvs->y_max = height;
	if (!(cvs->mlx = mlx_init())
		|| !(cvs->win = mlx_new_window(cvs->mlx, width, height, "Wolf3D"))
		|| !(cvs->img = mlx_new_image(cvs->mlx, width, height))
		|| !(cvs->data = (int *)mlx_get_data_addr(cvs->img,
			&cvs->bpp, &cvs->lsize, &cvs->endian)))
		DEFAULT_ERROR;
}

static int	game_loop(t_map *map)
{
	if (map->keys[1])
		move(map, 1);
	else if (map->keys[2])
		move(map, -1);
	if (map->keys[3])
		turn(map->pos, 1);
	else if (map->keys[4])
		turn(map->pos, -1);
	raycast(map);
	mlx_put_image_to_window(map->cvs->mlx, map->cvs->win, map->cvs->img, 0, 0);
	return (0);
}

int			main(int ac, char **av)
{
	t_map	*map;

	if (ac != 2)
		FATAL_ERROR("usage: wolf3d <map-filename>");
	map = load_map(av[1]);
	if (map->arr[(int)map->pos->loc_y][(int)map->pos->loc_x] > 0)
		MAP_ERROR;
	init_canvas(map->cvs, 1920, 1080);
	map->pos->dir_x = -1;
	map->pos->dir_y = 0;
	map->pos->plane_x = 0;
	map->pos->plane_y = 0.66;
	mlx_hook(map->cvs->win, 2, 1, &keydown_handler, map);
	mlx_hook(map->cvs->win, 17, 1, &close_window, map);
	mlx_key_hook(map->cvs->win, &keyup_handler, map);
	mlx_loop_hook(map->cvs->mlx, &game_loop, map);
	mlx_loop(map->cvs->mlx);
	return (0);
}
