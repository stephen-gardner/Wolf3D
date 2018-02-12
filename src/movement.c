/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 22:33:42 by sgardner          #+#    #+#             */
/*   Updated: 2018/02/12 04:05:20 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

#define ROT 0.0225
#define MOV 0.0375

void	move(t_map *map, int dir)
{
	t_pos	*pos;
	double	dx;
	double	dy;

	pos = map->pos;
	dx = (pos->dir_x * MOV) * dir;
	dy = (pos->dir_y * MOV) * dir;
	if (!map->arr[(int)pos->loc_y][(int)(pos->loc_x + dx)])
		pos->loc_x += dx;
	if (!map->arr[(int)(pos->loc_y + dy)][(int)pos->loc_x])
		pos->loc_y += dy;
}

void	turn(t_pos *pos, int dir)
{
	double	ang;
	double	tmp;

	ang = ROT * dir;
	tmp = pos->dir_x;
	pos->dir_x = (pos->dir_x * cos(ang)) - (pos->dir_y * sin(ang));
	pos->dir_y = (tmp * sin(ang)) + (pos->dir_y * cos(ang));
	tmp = pos->plane_x;
	pos->plane_x = (pos->plane_x * cos(ang)) - (pos->plane_y * sin(ang));
	pos->plane_y = (tmp * sin(ang)) + (pos->plane_y * cos(ang));
}
