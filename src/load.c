/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 21:15:48 by sgardner          #+#    #+#             */
/*   Updated: 2018/02/03 01:40:22 by sgardner         ###   ########.fr       */
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

static int	map_atoi(char *str)
{
	long	n;

	n = 0;
	if (!*str)
		DEFAULT_ERROR;
	while (*str)
	{
		if (!IS_DIGIT(*str) || BUILD_NUM(n, *str++) > INT_MAX)
			MAP_ERROR;
	}
	return ((int)n);
}

static void	load_data(t_map *map, char *line, int height)
{
	char	**arr;
	int		pos;
	int		i;

	i = 0;
	arr = split(line);
	pos = height * map->width;
	while (arr[i])
	{
		if (i == map->width)
			break ;
		map->data[pos + i] = map_atoi(arr[i]);
		++i;
	}
	if (i != map->width || arr[i])
		MAP_ERROR;
	free(arr);
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
		BUILD_NUM(map->width, key[i++]);
	if (!map->width || key[i++] != 'x')
		MAP_ERROR;
	while (key[i] && IS_DIGIT(key[i]))
		BUILD_NUM(map->height, key[i++]);
	if (!map->height || key[i] != '\n')
		MAP_ERROR;
}

t_map		*load_map(char *path)
{
	t_map	*map;
	char	*line;
	int		height;
	int		bytes;
	int		fd;

	if (!(map = ft_memalloc(sizeof(t_map))))
		DEFAULT_ERROR;
	if ((fd = open(path, O_RDONLY)) < 0)
		DEFAULT_ERROR;
	read_key(map, fd);
	if (!(map->data = ft_memalloc(sizeof(int) * (map->width * map->height))))
		DEFAULT_ERROR;
	height = 0;
	while ((bytes = get_next_line(fd, &line)) > 0)
	{
		load_data(map, line, height++);
		free(line);
	}
	close(fd);
	if (bytes < 0)
		DEFAULT_ERROR;
	if (height != map->height)
		MAP_ERROR;
	return (map);
}
