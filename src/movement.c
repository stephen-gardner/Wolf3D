/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 22:33:42 by sgardner          #+#    #+#             */
/*   Updated: 2018/02/12 09:02:28 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "wolf3d.h"

int		keydown_handler(int key, t_map *map)
{
	if (key == K_SP)
		map->keys[0] = TRUE;
	else if (key == K_W || key == K_UP)
		map->keys[1] = TRUE;
	else if (key == K_S || key == K_DN)
		map->keys[2] = TRUE;
	else if (key == K_A || key == K_LT)
		map->keys[3] = TRUE;
	else if (key == K_D || key == K_RT)
		map->keys[4] = TRUE;
	else if (key == K_ESC)
		exit(0);
	return (0);
}

int		keyup_handler(int key, t_map *map)
{
	if (key == K_SP)
		map->keys[0] = FALSE;
	else if (key == K_W || key == K_UP)
		map->keys[1] = FALSE;
	else if (key == K_S || key == K_DN)
		map->keys[2] = FALSE;
	else if (key == K_A || key == K_LT)
		map->keys[3] = FALSE;
	else if (key == K_D || key == K_RT)
		map->keys[4] = FALSE;
	return (0);
}

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
