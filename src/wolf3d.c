/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 21:07:24 by sgardner          #+#    #+#             */
/*   Updated: 2018/02/04 00:38:17 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "wolf3d.h"

static void	init_canvas(t_canvas *cvs, int width, int height)
{
	cvs->width = width;
	cvs->height = height;
	if (!(cvs->mlx = mlx_init())
		|| !(cvs->win = mlx_new_window(cvs->mlx, width, height, "Wolf3D"))
		|| !(cvs->img = mlx_new_image(cvs->mlx, width, height))
		|| !(cvs->data = (int *)mlx_get_data_addr(cvs->img,
			&cvs->bpp, &cvs->line_size, &cvs->endian)))
		DEFAULT_ERROR;
}

int			main(int ac, char **av)
{
	t_map	*map;

	if (ac != 2)
		FATAL_ERROR("usage: wolf3d <map-filename>\n");
	map = load_map(av[1]);
	init_canvas(map->canvas, 800, 600);
	return (0);
}
