/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 22:18:46 by sgardner          #+#    #+#             */
/*   Updated: 2018/02/12 09:30:41 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "wolf3d.h"

void		fatal_error(char *msg)
{
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
	exit(1);
}

int			get_color(t_raycast *rc, int y)
{
	if (rc->face == NORTH)
	{
		if (y % 5)
			return (0);
		return (0xFFFF00);
	}
	else if (rc->face == SOUTH)
	{
		if (rc->x % 5)
			return (0);
		return (0x00FF00);
	}
	else if (rc->face == EAST)
	{
		if (y % 5 || rc->x % 10)
			return (0);
		return (0xFFFFFF);
	}
	else
		return (0xFF0000);
}

static int	count_args(char *arg)
{
	int	count;

	count = 0;
	while (*arg)
	{
		if (*arg != ' ' && (*(arg + 1) == ' ' || *(arg + 1) == '\0'))
			count++;
		arg++;
	}
	return (count);
}

char		**split(char *arg)
{
	char	**arr;
	int		size;
	int		i;

	size = count_args(arg);
	if (!(arr = ft_memalloc(sizeof(char *) * (size + 1))))
		DEFAULT_ERROR;
	i = 0;
	while (*arg)
	{
		while (*arg == ' ')
			*arg++ = '\0';
		if (*arg)
			arr[i++] = arg;
		while (*arg && *arg != ' ')
			arg++;
	}
	return (arr);
}
