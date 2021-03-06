/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 21:15:48 by sgardner          #+#    #+#             */
/*   Updated: 2018/02/12 07:32:02 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <limits.h>
#include <stdlib.h>
#include <unistd.h>
#include "get_next_line.h"
#include "wolf3d.h"

#define IS_DIGIT(x) ((unsigned int)(x - '0') < 9)
#define BUILD_NUM(x, y) (x = (x * 10) + (y - '0'))

static void	force_border(t_map *map)
{
	int	i;

	i = 0;
	while (i < map->x_max)
	{
		map->arr[0][i] = 1;
		map->arr[map->y_max - 1][i] = 1;
		i++;
	}
	i = 0;
	while (i < map->y_max)
	{
		map->arr[i][0] = 1;
		map->arr[i][map->x_max - 1] = 1;
		i++;
	}
}

static int	map_atoi(char *str)
{
	long	n;

	n = 0;
	if (!*str)
		DEFAULT_ERROR;
	while (*str)
	{
		if (*str == 'S')
			return (-1);
		if (!IS_DIGIT(*str) || BUILD_NUM(n, *str++) > INT_MAX)
			MAP_ERROR;
	}
	return ((int)n);
}

static void	load_data(t_map *map, char *line, int y)
{
	char	**arr;
	int		x;

	x = 0;
	arr = split(line);
	map->arr[y] = &map->raw[y * map->x_max];
	while (x < map->x_max && arr[x])
	{
		if ((map->arr[y][x] = map_atoi(arr[x])) < 0)
		{
			map->arr[y][x] = 0;
			map->pos->loc_x = x;
			map->pos->loc_y = y;
		}
		++x;
	}
	if (x != map->x_max || arr[x])
		MAP_ERROR;
	free(arr);
	free(line);
}

static void	read_key(t_map *map, int fd)
{
	static char	key[23];
	int			i;

	i = 0;
	while (TRUE)
	{
		if (i > 22 || read(fd, &key[i], 1) < 1)
			MAP_ERROR;
		if (key[i] == '\n')
			break ;
		++i;
	}
	i = 0;
	while (key[i] && IS_DIGIT(key[i]))
		BUILD_NUM(map->x_max, key[i++]);
	if (!map->x_max || key[i++] != 'x')
		MAP_ERROR;
	while (key[i] && IS_DIGIT(key[i]))
		BUILD_NUM(map->y_max, key[i++]);
	if (!map->y_max || key[i] != '\n')
		MAP_ERROR;
}

t_map		*load_map(char *path)
{
	t_map	*map;
	char	*line;
	int		bytes;
	int		fd;
	int		y;

	if (!(map = ft_memalloc(sizeof(t_map))))
		DEFAULT_ERROR;
	if ((fd = open(path, O_RDONLY)) < 0)
		DEFAULT_ERROR;
	read_key(map, fd);
	if (!(map->raw = ft_memalloc(sizeof(int) * (map->x_max * map->y_max)))
		|| !(map->cvs = ft_memalloc(sizeof(t_canvas)))
		|| !(map->pos = ft_memalloc(sizeof(t_pos)))
		|| !(map->arr = ft_memalloc(sizeof(int *) * map->y_max)))
		DEFAULT_ERROR;
	y = 0;
	while ((bytes = get_next_line(fd, &line)) > 0)
		load_data(map, line, y++);
	close(fd);
	if (y != map->y_max)
		MAP_ERROR;
	force_border(map);
	return (map);
}
